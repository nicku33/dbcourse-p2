#!/bin/bash


# first let's compile what we need

make genfile || exit $?
make splashapp || exit $?
make probeapp || exit $?

./gen 4 9 15 2 test_probe.txt test_input.txt || exit $?
./splash 4 9 15 2 test_input.txt test_dump.txt < test_probe.txt > test_result.txt || exit $?
./probe test_dump.txt < test_probe.txt > test_result_simd.txt || exit $?

diff test_result.txt test_result_simd.txt  || exit $?
