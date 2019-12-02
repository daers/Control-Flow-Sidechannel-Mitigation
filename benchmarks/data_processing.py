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

for idx, df in enumerate(statistics):
	print("Data for data frame " + idx)
	print("Zero Average: " + df["zero_avg"].mean())
	print("One Average: " + df["one_avg"].mean())
	print("Diff Average: " + df["diff"].mean())
	print("\n")



# class Stats_Info:
# 	def __init__(self, exp, zero_avg, zero_stdev, one_avg, one_stdev, diff):
# 	    self.exp = exp
# 	    self.zero_avg = zero_avg
# 	    self.zero_stdev = zero_stdev
# 	    self.one_avg = one_avg
# 	    self.one_stdev = one_stdev
# 	    self.diff = diff

# class File_Stats:
# 	def __init__(self, name_in, data_in):
# 		name = name_in
# 		data = data_in.copy()

# 	def append_stats(self, new_value):
# 		self.stats_list.append(new_value)

# for filename in os.listdir(stats_directory):
# 	if filename.endswith(".csv"):
# 		filename_complete = stats_directory + filename
# 		with open(filename_complete, "r") as stats_file:
# 			current_file = File_Stats()
# 			readCSV = csv.reader(stats_file, delimiter='\t')
# 			for row in readCSV:
# 				row_stats = Stats_Info(row[0], row[1], row[2], row[3], row[4], row[5])
# 				current_file.append_stats(row_stats)
# 			statistics.append(current_file)

