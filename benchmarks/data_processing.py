import csv, os
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as stats
from scipy.stats import norm
import math


statistics = []

def main():
    repo_directory = os.path.expanduser("~/Control-Flow-Sidechannel-Mitigation")
    stats_directory = os.path.join(repo_directory, "benchmarks/out_dir/")

    filenames = []

    for filename in os.listdir(stats_directory):
        if filename.endswith(".csv"):
            filename_complete = stats_directory + filename
            data = pd.read_csv(filename_complete, sep='\t')
            graph_normal(data)
            return

            statistics.append(data)

    print_all(statistics)

def print_empty_line():
    print("~")

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

def graph_normal(df):
    z_mean = df["zero_avg"].mean()
    z_std = df["zero_avg"].std()
    o_mean = df["one_avg"].mean()
    o_std = df["one_avg"].std()

    x_axis = np.arange(min(z_mean - 3*z_std, o_mean - 3*o_std), max(z_mean + 3*z_std, o_mean + 3*o_std), 0.001)

    plt.plot(x_axis, norm.pdf(x_axis, z_mean,z_std), 'C1', label='zero')
    plt.plot(x_axis, norm.pdf(x_axis, z_mean,z_std), 'C2', label='one')
    plt.savefig("save.png")
    plt.show()
    plt.close()


if __name__ == '__main__':
    main()
