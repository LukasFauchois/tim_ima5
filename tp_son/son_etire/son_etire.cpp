#include <iostream>
#include "../wavdata.h"
#include "../fft.h"
#include <math.h>

#include <fstream>
using namespace std;

#define FREQUENCY 44100
#define SIZE FREQUENCY*2
#define AMPLITUDE 10
#define PI 3.1415
#define LA 440

int main(int argc, char **argv)
{
  WavData w;
	char *data = new char[SIZE];

  WavData w1;
	w1.load("../COW.WAV");
	char *data1 = w1.data();

	int i;
  for(i=0;i<SIZE;i++){
    float t = (i*1.0)/FREQUENCY;
    float omega = 2.0*M_PI*LA;
    data[i]=AMPLITUDE*(sin(omega*t)+1);
  }

  w.setAudioFormat(1); //1 pour pcm
  w.setNbrChanel(1); // 2 canaux car stéréo
  w.setFrequency(FREQUENCY); //fréquence d'échantillage
  w.setBytePerSec(FREQUENCY); //= freq
  w.setBytePerBloc(1); // 1 octets par bloc
  w.setBitsPerSample(8); // 8 bits par échantillon (car 1 octet)
  w.clearData();
  w.setDatasize(SIZE);
  w.setData(data);

  char *long_data = new char[SIZE*2];
  char *long_data_cow = new char[w1.datasize()*2];

  for(int i=0;i<w.datasize();i++){
    long_data[i*2]= data[i];
    long_data[(i*2)+1]= data[i];
  }

  for(int i=0;i<w1.datasize();i++){
    long_data_cow[i*2]= data1[i];
    long_data_cow[(i*2)+1]= data1[i];
  }

 w.clearData();
 w.setDatasize(SIZE*2);
 w.setData(long_data);
 w.save("SON_PUR_ETIRE.WAV");

 w1.clearData();
 w1.setDatasize(w1.datasize()*2);
 w1.setData(long_data_cow);
 w1.save("COW_ETIRE.WAV");

  return 0;
}
