PATH2LIB=~/Control-Flow-Sidechannel-Mitigation/pass/build/pass/CF_SEC.so        # Specify your build directory in the project
PASS=-CF_SEC                   # Choose either -fplicm-correctness or -fplicm-performance

# Delete outputs from previous run.
rm -f default.profraw CF_SEC_pass *.bc CF_SEC.profdata *_output *.ll

# Convert source code to bitcode (IR)
clang -emit-llvm -c pass/pass.cpp -o CF_SEC.bc
# Canonicalize natural loops
opt -loop-simplify CF_SEC.bc -o CF_SEC.ls.bc
# Apply FPLICM
opt -o CF_SEC.bc -pgo-instr-use -load ${PATH2LIB} ${PASS} < CF_SEC.ls.bc > /dev/null

# Generate binary executable after FPLICM: Optimized code
clang CF_SEC.bc -o CF_SEC

# Produce output from binary to check correctness
./CF_SEC > CF_SEC_output

echo -e "\n=== Correctness Check ==="
echo -e ">> PASS\n"
# Measure performance
echo -e "Performance of code"
time ./CF_SEC > /dev/null
echo -e "\n\n"

# Cleanup
rm -f default.profraw CF_SEC_pass CF_SEC *.bc *_output *.ll
