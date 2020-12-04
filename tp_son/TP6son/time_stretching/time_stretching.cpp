#include <iostream>
#include "../wavdata.h"
#include "../fft.h"
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
  int *size;
  size = (int*)malloc(sizeof(int));
  *size = SIZE;

//Variables pour son pur
  WavData w;
  char *data = new char[*size];
  char *new_data = new char[*size];

  double audio[*size][2];
  double fft_out[*size][2];
  double long_audio_f[*size*2][2];
  double long_audio_t[*size][2];

//TIME-STRETCHING PUR
	int i;
  for(i=0;i<*size;i++){
    float t = (i*1.0)/FREQUENCY;
    float omega = 2.0*M_PI*LA;
    data[i]=AMPLITUDE*(sin(omega*t)+1);
    audio[i][0]=(double)data[i];
    audio[i][1]=0;
  }

  fft(N, audio, fft_out);

  for(int i=0;i<*size*2;i+=2){
    long_audio_f[i][0]=fft_out[i][0];
    long_audio_f[i+1][0]=fft_out[i][0];
    long_audio_f[i][1]=fft_out[i][1];
    long_audio_f[i+1][1]=fft_out[i][1];
  }

 ifft(N, long_audio_t, long_audio_f);

 for(int i=0;i<*size;i++){
   new_data[i] = long_audio_t[i][0];
 }

 w.setAudioFormat(1); //1 pour pcm
 w.setNbrChanel(1); // 2 canaux car stéréo
 w.setFrequency(FREQUENCY); //fréquence d'échantillage
 w.setBytePerSec(FREQUENCY); //= freq
 w.setBytePerBloc(1); // 1 octets par bloc
 w.setBitsPerSample(8); // 8 bits par échantillon (car 1 octet)
 w.clearData();
 w.setDatasize(*size);
 w.setData(new_data);
 w.save("TIME_STRETCHING_PUR.WAV");

 free(size);


/*
//Variables pour son complexe
  int *size_cow;
  size_cow = (int*)malloc(sizeof(int));


  WavData w1;
	w1.load("../COW.WAV");
  *size_cow = w1.datasize();

	char *data1 = w1.data();
  char *new_data1 = new char[*size_cow];


  printf("here\n");

  double audio_cow[*size_cow][2];
  double fft_out_cow[*size_cow][2];
  double long_audio_f_cow[*size_cow*2][2];
  double long_audio_t_cow[*size_cow][2];

  printf("here\n");

 //TIME-STRETCHING COW
  for(i=0;i<*size_cow;i++){
    audio_cow[i][0]=(double)data1[i];
    audio_cow[i][0]=0;
  }

  printf("here\n");

  fft(N, audio_cow, fft_out_cow);

  printf("here\n");

  for(int i=0;i<*size_cow*2;i+=2){
    long_audio_f_cow[i][0]=fft_out_cow[i][0];
    long_audio_f_cow[i+1][0]=fft_out_cow[i][0];
    long_audio_f_cow[i][1]=fft_out_cow[i][1];
    long_audio_f_cow[i+1][1]=fft_out_cow[i][1];
  }

  printf("here\n");

 ifft(N, long_audio_t_cow, long_audio_f_cow);

  printf("here\n");

 for(int i=0;i<*size_cow;i++){
   new_data1[i] = long_audio_t_cow[i][0];
 }

 printf("here\n");

 w1.clearData();
 w1.setDatasize(*size_cow);
 w1.setData(new_data1);
 w1.save("TIME_STRETCHING_COW.WAV");
 free(size_cow);*/
}
