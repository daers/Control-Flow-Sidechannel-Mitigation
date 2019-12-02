BENCH=../benchmarks/${1}
PATH_OUT=../benchmarks/out_dir/pre_pass.csv

rm ${BENCH}.bc

# Convert source code to bitcode (IR)
# This approach has an issue with -O2, so we are going to stick with default optimization level (-O0)
clang -emit-llvm -c ${BENCH}.c -o ${BENCH}.bc -S

clang ${BENCH}.bc -o passed_code

./passed_code > stats 

python stats.py > ${PATH_OUT}

rm passed_code stats

