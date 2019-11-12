PATH2LIB=~/Control-Flow-Sidechannel-Mitigation/build/pass/CF_SEC.so        # Specify your build directory in the project
PASS=CF_SEC                   # Choose either -fplicm-correctness or -fplicm-performance

# Delete outputs from previous run.
rm -f default.profraw CF_SEC_prof CF_SEC_fplicm CF_SEC_no_fplicm *.bc CF_SEC.profdata *_output *.ll

# Convert source code to bitcode (IR)
clang -emit-llvm -c pass/pass.cpp -o CF_SEC.bc
# Canonicalize natural loops
opt -loop-simplify CF_SEC.bc -o CF_SEC.ls.bc
# Instrument profiler
# opt -pgo-instr-gen -instrprof CF_SEC.ls.bc -o CF_SEC.ls.prof.bc
# Generate binary executable with profiler embedded
# clang -fprofile-instr-generate CF_SEC.ls.prof.bc -o CF_SEC_prof

# Generate profiled data
#./CF_SEC_prof > correct_output
#llvm-profdata merge -o CF_SEC.profdata default.profraw

# Apply FPLICM
opt -o CF_SEC.bc -pgo-instr-use -load ${PATH2LIB} ${PASS} < CF_SEC.ls.bc > /dev/null

# Generate binary executable after FPLICM: Optimized code
clang CF_SEC.bc -o CF_SEC

# Produce output from binary to check correctness
./CF_SEC > CF_SEC_output

echo -e "\n=== Correctness Check ==="
if [ "$(diff correct_output fplicm_output)" != "" ]; then
    echo -e ">> FAIL\n"
else
    echo -e ">> PASS\n"
    # Measure performance
    echo -e "Performance of code"
    time ./CF_SEC > /dev/null
    echo -e "\n\n"
fi

# Cleanup
rm -f default.profraw CF_SEC_prof CF_SEC *.bc CF_SEC.profdata *_output *.ll
