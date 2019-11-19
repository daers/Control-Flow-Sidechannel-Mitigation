CC = gcc
LD = gcc

# specify compile and link options
CFLAGS = -c -std=c11
LFLAGS = -Wall -lm
POSTFLAGS = -lm

OBJS = rsa_time_c11.o stats_counter.o
EX = rsa

# following asks for both executables to be built
default:  $(EX)

# to build this executable, check to see if any of the listed object files
# need to be rebuilt and do so, then link to create the executable
$(EX): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(EX) $(POSTFLAGS)

# to build this object module, check the timestamps of what it depends on, and
# if any are more recent than an existing p1_main.o, then recompile p1_main.c
rsa_time_c11.o: rsa_time_c11.c 
	$(CC) $(CFLAGS) rsa_time_c11.c

stats_counter.o: stats_counter.h stats_counter.c
	$(CC) $(CFLAGS) stats_counter.c

# other shell commands can appear as "things to do" - not just compilations, etc.
clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f $(EX)


