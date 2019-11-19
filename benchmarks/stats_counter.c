#include "stats_counter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SC_init(struct stats_counter* sc) {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 64; ++j) {
			sc->times[i][j] = 0;
		}
		sc->averages[i] = 0;
		sc->stdDevs[i] = 0;
	}
	sc->averagesReady = 0;
}

void SC_addTick(struct stats_counter* sc, int bit, int index, uint64_t elapsed) {
	sc->times[bit][index] = elapsed;
}

void SC_calculateStats(struct stats_counter* sc) {
	SC_calculateAverages(sc);
	SC_calculateStdDevs(sc);
}

void SC_calculateAverages(struct stats_counter* sc) {
	long totals[2], counts[2];
	totals[0] = 0, totals[1] = 0, counts[0] = 0, counts[1] = 0;
	for (int i = 0; i < 64; ++i) {
		if (sc->times[0][i]) {
			totals[0] += sc->times[0][i];
			++counts[0];
		} else {
			totals[1] += sc->times[1][i];
			++counts[1];
		}
	}
	sc->averages[0] = totals[0] / counts[0];
	sc->averages[1] = totals[1] / counts[1];
	// mark averagesReady for calculateStdDevs
	sc->averagesReady = 1;
	printf("\t0\t1\n");
	printf("Avgs.:\t%ld\t%ld\n", sc->averages[0], sc->averages[1]);
}

void SC_calculateStdDevs(struct stats_counter* sc) {
	long sumsOfDiffs[2];
	sumsOfDiffs[0] = 0, sumsOfDiffs[1] = 0;
	if (!sc->averagesReady) {
		SC_calculateAverages(sc);
	}
	for (int i = 0; i < 2; ++i) {
		float total = 0.;
		for (int j = 0; j < 64; ++j) {
			if (sc->times[i][j]) {
				float diff = abs(sc->times[i][j] - sc->averages[i]);
				sumsOfDiffs[i] += diff * diff;
				++total;
			}
		}
		sumsOfDiffs[i] /= total;
		sc->stdDevs[i] = sqrt(sumsOfDiffs[i]);
	}
	printf("Std.:\t%ld\t%ld\nDevs.\n", sc->stdDevs[0], sc->stdDevs[1]);
}

