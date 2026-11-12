#!/bin/bash
set -e
cd "$(dirname "$0")"
rm -rf obj_dir

verilator -Wall --cc rtl/control_unit.sv \
    --exe tests/verify_control_unit.cpp \
    --top-module control_unit \
    -CFLAGS "-std=c++17" \
    -LDFLAGS "-lgtest -lpthread" \
    --build -j 4

obj_dir/Vcontrol_unit