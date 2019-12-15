from math import sqrt


def std_dev(ticks, avg):
    var = 0
    for tick in ticks:
        diff = abs(tick - avg)
        var += diff * diff
    var /= len(ticks)
    return sqrt(var)


def avg(ticks):
    return sum(ticks) / len(ticks)


def calculate_stats(exp_dict):
    zero_ticks = exp_dict[0]
    one_ticks = exp_dict[1]
    zero_avg = avg(zero_ticks)
    one_avg = avg(one_ticks)
    print("\tavg.\tstd. dev.")
    print("0:\t" + str(zero_avg) + "\t" + str(std_dev(zero_ticks, zero_avg)))
    print("1:\t" + str(one_avg) + "\t" + str(std_dev(one_ticks, one_avg)))
    print("Diff:\t" + str(one_avg - zero_avg))
    print("\n")

# PRINT IN FORMAT: exp zero_avg zero_stdev one_avg one_stdev diff
def calculate_stats_for_processing(exp_dict, exp):
    z_ticks = exp_dict[0]
    o_ticks = exp_dict[1]
    z_avg = avg(z_ticks)
    o_avg = avg(o_ticks)
    z_stdev = std_dev(z_ticks, z_avg)
    o_stdev = std_dev(o_ticks, o_avg)
    diff_avg = (o_avg - z_avg)
    print(str(exp) + "\t" + str(z_avg) + "\t" + str(z_stdev) + "\t" + str(o_avg) + "\t" + str(o_stdev) + "\t" + str(diff_avg))

cycles_dict = {}
for line in open("stats", 'r').readlines()[1:]:
    exp, bit, cycles = line.split()
    exp = long(exp)
    bit = int(bit)
    cycles = long(cycles)
    if exp not in cycles_dict:
        cycles_dict[exp] = {}
    if bit not in cycles_dict[exp]:
        cycles_dict[exp][bit] = []
    cycles_dict[exp][bit].append(cycles)

# Block 2 is more readable. Block 1 is for generating CSV file.
# One should be commented out.
print("exp\tzero_avg\tzero_stdev\tone_avg\tone_stdev\tdiff") # Block 1
for exp in cycles_dict:
    # print("Exp:\t" + str(exp)) # Block 2
    # calculate_stats(cycles_dict[exp]) # Block 2
    calculate_stats_for_processing(cycles_dict[exp], exp) # Block 1
