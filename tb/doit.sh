#!/bin/bash
# Runs every unit test in tests/ (or just the ones you name) and reports a summary.
#
# Usage (from anywhere)
#   ./doit.sh                                  run all tests
#   ./doit.sh tests/verify_alu.cpp             run one test
#
# Naming rule
#   tests/verify_<name>.cpp tests rtl/<name>.sv
#   e.g. tests/verify_regfile.cpp -> rtl/regfile.sv
#   The module name is read from inside the .sv file, so it may differ
#   from the file name (e.g. pc.sv contains module Pc_counter).

cd "$(dirname "$(realpath "$0")")"   # always run from the repo root

GREEN=$(tput setaf 2 2>/dev/null); RED=$(tput setaf 1 2>/dev/null); RESET=$(tput sgr0 2>/dev/null)

if [[ $# -eq 0 ]]; then
    tests=(tests/verify_*.cpp)
else
    tests=("$@")
fi

passes=0
fails=0
failed_names=()

rm -rf obj_dir && mkdir -p obj_dir

for test in "${tests[@]}"; do
    name=$(basename "$test" .cpp)
    name=${name#verify_}
    sv="../rtl/${name}.sv"

    echo
    echo "===== ${name} ====="

    if [[ ! -f "$sv" ]]; then
        echo "${RED}No ${sv} found for ${test}${RESET}"
        ((fails++)); failed_names+=("$name"); continue
    fi

    # First "module X" in the file is the module under test
    top=$(grep -m1 -oP '^\s*module\s+\K\w+' "$sv")

    if verilator -Wall --trace --cc "$sv" \
            --exe "$(realpath "$test")" \
            -y ../rtl \
            --top-module "$top" \
            --Mdir "obj_dir/${name}" \
            -CFLAGS "-std=c++17" \
            -LDFLAGS "-lgtest -lpthread" \
            --build -j 4 > "obj_dir_${name}.log" 2>&1 \
       && "./obj_dir/${name}/V${top}"; then
        ((passes++))
    else
        [[ -f "obj_dir/${name}/V${top}" ]] || { echo "${RED}Build failed${RESET}"; cat "obj_dir_${name}.log"; }
        ((fails++)); failed_names+=("$name")
    fi
    rm -f "obj_dir_${name}.log"
done

echo
total=$((passes + fails))
if [[ $fails -eq 0 ]]; then
    echo "${GREEN}Success! All ${passes} test file(s) passed.${RESET}"
    exit 0
else
    echo "${RED}Failure. ${passes} of ${total} test file(s) passed. Failed: ${failed_names[*]}${RESET}"
    exit 1
fi
