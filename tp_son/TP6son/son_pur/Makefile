CC = g++
CFLAGS = -Wall -Wextra
LDFLAGS =
EXEC = son_pur
OPT1 = -lm


all : $(EXEC)

son_pur : son_pur.o ../fft.o ../wavdata.o
	$(CC) $(OPT1) $^ -o $@

son_pur.o : son_pur.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

../fft.o : ../fft.cpp ../fft.h
	$(CC) -o $@ -c $< $(CFLAGS)

../wavdata.o : ../wavdata.cpp ../wavdata.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o *.WAV *.csv

mrproper: clean
	rm -rf $(EXEC)
