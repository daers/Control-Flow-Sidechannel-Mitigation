import csv, os
import pandas as pd
import matplotlib.pyplot as plt

statistics = []

def main():
    repo_directory = os.path.expanduser("~/Control-Flow-Sidechannel-Mitigation")
    stats_directory = os.path.join(repo_directory, "benchmarks/out_dir/")

    filenames = []

    for filename in os.listdir(stats_directory):
    	if filename.endswith(".csv"):
    		filename_complete = stats_directory + filename
    		data = pd.read_csv(filename_complete, sep='\t')
    		# current_file = File_Stats(filename_complete, data)

    		statistics.append(data)

    print_all(statistics)

def print_empty_line():
	print("~                                    ~")

def print_full_line():
	print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

def print_header():
	print("\n")
	print_full_line()
	print("~    PRE AND POST PASS STATISTICS    ~")
	print_full_line()
	print_empty_line()
	print_empty_line()

def print_footer():
	print_empty_line()
	print_full_line()

def print_all(statistics):
	tilde = "~  "
	print_header()
	for idx, df in enumerate(statistics):
		print_empty_line()
		print(tilde + "Data for data frame " + str(idx))
		print(tilde + "Zero Average: " + str(df["zero_avg"].mean()))
		print(tilde + "Zero stdev: " + str(df["zero_avg"].std()))
		print(tilde + "One Average: " + str(df["one_avg"].mean()))
		print(tilde + "One stdev: " + str(df["one_avg"].std()))
		print(tilde + "Diff Average: " + str(df["diff"].mean()))
		print_empty_line()
	print_footer()

if __name__ == '__main__':
    main()







