CC = g++
CFLAGS = -Wall -Wextra
LDFLAGS =
EXEC = time_stretching
OPT1 = -lm


all : $(EXEC)

time_stretching : time_stretching.o ../fft.o ../wavdata.o
	$(CC) $(OPT1) $^ -o $@

time_stretching.o : time_stretching.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

../fft.o : ../fft.cpp ../fft.h
	$(CC) -o $@ -c $< $(CFLAGS)

../wavdata.o : ../wavdata.cpp ../wavdata.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o *.WAV

mrproper: clean
	rm -rf $(EXEC)
