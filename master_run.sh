# To run, do: ./master_run.sh name_of_benchmark
# You will need to pip install pandas and matplotlib
BENCH=${1}

# Gather data pre pass and post pass
cd pass
./run.sh ${BENCH}

./no_pass.sh ${BENCH}

cd ../benchmarks

python3 data_processing.py

cd ../
