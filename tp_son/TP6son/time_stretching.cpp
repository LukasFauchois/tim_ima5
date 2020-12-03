#include <iostream>
#include "wavdata.h"
#include "fft.h"
#include <math.h>

#include <fstream>
using namespace std;

#define FREQUENCY 44100
#define SIZE FREQUENCY*2
#define AMPLITUDE 10
#define LA 440
#define N 65536

int main(int argc, char **argv)
{
//Variables pour son pur
  WavData w;
  char *data = new char[SIZE];
  char *new_data = new char[SIZE];

  double audio[SIZE][2];
  double fft_out[SIZE][2];
  double long_audio_f[SIZE*2][2];
  double long_audio_t[SIZE][2];

//Variables pour son complexe
  WavData w1;
	w1.load("COW.WAV");
	char *data1 = w1.data();
  char *new_data1 = new char[SIZE];

  double audio_cow[SIZE][2];
  double fft_out_cow[SIZE][2];
  double long_audio_f_cow[SIZE*2][2];
  double long_audio_t_cow[SIZE][2];

 //TIME-STRETCHING PUR
	int i;
  for(i=0;i<SIZE;i++){
    float t = (i*1.0)/FREQUENCY;
    float omega = 2.0*M_PI*LA;
    data[i]=AMPLITUDE*(sin(omega*t)+1);
    audio[i][0]=(double)data[i];
    audio[i][1]=0;
  }

  fft(N, audio, fft_out);

  for(int i=0;i<SIZE*2;i+=2){
    long_audio_f[i][0]=fft_out[i][0];
    long_audio_f[i+1][0]=fft_out[i][0];
    long_audio_f[i][1]=fft_out[i][1];
    long_audio_f[i+1][1]=fft_out[i][1];
  }

 ifft(N, long_audio_t, long_audio_f);

 for(int i=0;i<SIZE;i++){
   new_data[i] = long_audio_t[i][0];
 }

 w.setAudioFormat(1); //1 pour pcm
 w.setNbrChanel(1); // 2 canaux car stéréo
 w.setFrequency(FREQUENCY); //fréquence d'échantillage
 w.setBytePerSec(FREQUENCY); //= freq
 w.setBytePerBloc(1); // 1 octets par bloc
 w.setBitsPerSample(8); // 8 bits par échantillon (car 1 octet)
 w.clearData();
 w.setDatasize(SIZE);
 w.setData(new_data);
 w.save("TIME_STRETCHING_PUR.WAV");

/*

 //TIME-STRETCHING COW
  for(i=0;i<w1.datasize();i++){
    audio_cow[i][0]=(double)data1[i];
    audio_cow[i][0]=0;
  }

  fft(N, audio_cow, fft_out_cow);

  for(int i=0;i<w1.datasize()*2;i+=2){
    long_audio_f_cow[i][0]=fft_out_cow[i][0];
    long_audio_f_cow[i+1][0]=fft_out_cow[i][0];
    long_audio_f_cow[i][1]=fft_out_cow[i][1];
    long_audio_f_cow[i+1][1]=fft_out_cow[i][1];
  }

 ifft(N, long_audio_t_cow, long_audio_f_cow);

 for(int i=0;i<w1.datasize();i++){
   new_data1[i] = long_audio_t_cow[i][0];
 }

 w1.setDatasize(w1.datasize());
 w1.clearData();
 w1.setData(new_data1);
 w1.save("TIME_STRETCHING_COW.WAV");*/
}
