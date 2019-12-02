import csv, os
import pandas as pd
import matplotlib.pyplot as plt

repo_directory = os.path.expanduser("~/Control-Flow-Sidechannel-Mitigation")
stats_directory = os.path.join(repo_directory, "benchmarks/out_dir/")

filenames = []
statistics = []

for filename in os.listdir(stats_directory):
	if filename.endswith(".csv"):
		filename_complete = stats_directory + filename
		data = pd.read_csv(filename_complete, sep='\t')
		# current_file = File_Stats(filename_complete, data)

		statistics.append(data)

print("\n")
print("")
print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
print("~ PRE AND POST PASS STATISTICS ~")
print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
print("\n")

for idx, df in enumerate(statistics):
	print("Data for data frame " + str(idx))
	print("Zero Average: " + str(df["zero_avg"].mean()))
	print("Zero stdev: " + str(df["zero_avg"].std()))
	print("One Average: " + str(df["one_avg"].mean()))
	print("One stdev: " + str(df["one_avg"].std()))
	print("Diff Average: " + str(df["diff"].mean()))
	print("\n")



