#!/bin/bash


# first let's compile what we need

rm test_*.txt
make genapp || exit $?
make splashapp || exit $?
make probeapp || exit $?


./a.out 4 1000 15 2 test_probe.txt test_input.txt || exit $?
echo "test files generated"
./splash 4 1000 15 2 test_input.txt test_dump.txt < test_probe.txt > test_result.txt 
echo "tested with splash app"
./probe test_dump.txt < test_probe.txt > test_result_simd.txt || exit $?
echo "tested with simd"

diff -q test_result.txt test_result_simd.txt  || exit $?
