import csv, os
import numpy as np
import matplotlib.pyplot as plt

stats_directory = "./out_dir/"

filenames = []

for filename in os.listdir(current_in_directory):
	if filename.endswith(".csv"):
		filenames.append(filename)
		out_file = "out" + filename

		filename = current_in_directory + filename
		with open(filename, "r") as stats_file:
			readCSV = csv.reader(stats_file, delimiter=',')
			for row in readCSV:
				print(row)

	# for line in stats_file:
	# 	if sentinel % 4 == 1:

	# 	elif sentinel % 4 == 2:

	# 	sentinel++;
