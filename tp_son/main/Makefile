CC = g++
CFLAGS = -Wall -Wextra
LDFLAGS =
EXEC = main
OPT1 = -lm


all : $(EXEC)

main : main.o ../fft.o ../wavdata.o
	$(CC) $(OPT1) $^ -o $@

main.o : main.cpp
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
