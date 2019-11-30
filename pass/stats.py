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
    print("\n\n")


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

for exp in cycles_dict:
    print("\t" + str(exp))
    calculate_stats(cycles_dict[exp])


