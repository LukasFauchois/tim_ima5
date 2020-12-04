CC = g++
CFLAGS = -Wall -Wextra
LDFLAGS =
EXEC = son_etire
OPT1 = -lm


all : $(EXEC)

son_etire : son_etire.o ../fft.o ../wavdata.o
	$(CC) $(OPT1) $^ -o $@

son_etire.o : son_etire.cpp
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
