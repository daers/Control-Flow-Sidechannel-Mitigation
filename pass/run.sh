PATH2LIB=~/Control-Flow-Sidechannel-Mitigation/pass/build/pass/CF_SEC.so        # Specify your build directory in the project
PASS=-cf_sec                   # Choose either -fplicm-correctness or -fplicm-performance

# Delete outputs from previous run.
rm -f default.profraw rsa.bc *_output *.ll

# Convert source code to bitcode (IR)
clang -emit-llvm -c rsa.c -o rsa.bc
# Canonicalize natural loops
opt -loop-simplify rsa.bc -o rsa.ls.bc
# Apply FPLICM
opt -o rsa.bc -load ${PATH2LIB} ${PASS} < rsa.ls.bc > /dev/null

# Generate binary executable after FPLICM: Optimized code
clang rsa.bc -o RSA_EXEC

# Produce output from binary to check correctness
./RSA_EXEC > RSA_output

echo -e "\n=== Correctness Check ==="
echo -e ">> PASS\n"
# Measure performance
echo -e "Performance of code"
time ./RSA_EXEC > /dev/null
echo -e "\n\n"

# Cleanup
rm -f RSA_EXEC *.bc *_output *.ll
