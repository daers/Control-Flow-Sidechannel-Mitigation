#ifndef STATS_COUNTER_H
#define STATS_COUNTER_H

#include <stdint.h>

struct stats_counter {
	long times[2][64];
       	long averages[2];
	int averagesReady;
	long stdDevs[2];	
};

void SC_init(struct stats_counter* sc);

void SC_addTick(struct stats_counter* sc, int bit, int index, uint64_t elapsed);

void SC_calculateStats(struct stats_counter* sc);

void SC_calculateAverages(struct stats_counter* sc);

void SC_calculateStdDevs(struct stats_counter* sc);


#endif 
