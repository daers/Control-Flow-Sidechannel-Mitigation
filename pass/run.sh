cd build
make -j2
cd ..
#
# PATH2LIB=~/Control-Flow-Sidechannel-Mitigation/pass/build/pass/CF_SEC.so        # Specify your build directory in the project
# PASS=-cf_sec                   # Choose either -fplicm-correctness or -fplicm-performance
#
# # Delete outputs from previous run.
# rm -f default.profraw rsa.bc *_output *.ll
#
# # Convert source code to bitcode (IR)
# clang -emit-llvm -c rsa.c -o rsa.bc -S
# # Canonicalize natural loops
# opt -loop-simplify rsa.bc -o rsa.ls.bc -S
# # Apply FPLICM
# opt -o rsa.bc -load ${PATH2LIB} ${PASS} < rsa.ls.bc > /dev/null
#
# # Generate binary executable after FPLICM: Optimized code
# clang rsa.bc -o RSA_EXEC -
#
# # Produce output from binary to check correctness
# ./RSA_EXEC > RSA_output
#
# echo -e "\n=== Correctness Check ==="
# echo -e ">> PASS\n"
# # Measure performance
# echo -e "Performance of code"
# time ./RSA_EXEC > /dev/null
# echo -e "\n\n"


#!/bin/bash
### benchmark runner script
### Locate this script at each benchmark directory. e.g, 583simple/run.sh
### usage: ./run.sh ${benchmark_name} ${input}
### e.g., ./run.sh compress compress.in   or   ./run.sh simple

PATH_MYPASS=~/Control-Flow-Sidechannel-Mitigation/pass/build/pass/CF_SEC.so  ### Action Required: Specify the path to your pass ###
NAME_MYPASS=-cf_sec                            ### Action Required: Specify the name for your pass ###
BENCH=../benchmarks/${1}

rm ${BENCH}.bc

# Convert source code to bitcode (IR)
# This approach has an issue with -O2, so we are going to stick with default optimization level (-O0)
clang -emit-llvm -c ${BENCH}.c -o ${BENCH}.bc -S

# Apply your pass to bitcode (IR)
opt -load ${PATH_MYPASS} ${NAME_MYPASS} < ${BENCH}.bc > out -S

rm out.bc 
cp out out.bc && clang out.bc -o passed_code


./passed_code && rm out.bc

