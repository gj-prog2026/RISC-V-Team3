#!/bin/bash
set -e
cd "$(dirname "$0")"
rm -rf obj_dir

verilator -Wall --cc rtl/sign_extend.sv \
    --exe tests/verify_sign_extend.cpp \
    --top-module sign_extend \
    -CFLAGS "-std=c++17" \
    -LDFLAGS "-lgtest -lpthread" \
    --build -j 4

obj_dir/Vsign_extend