#include <iostream>
#include "../wavdata.h"
#include "../fft.h"
#include <math.h>

#include <fstream>
using namespace std;

#define FREQUENCY 22400
#define SIZE 32768
#define AMPLITUDE 10
#define LA 440
#define N 32768

int main(int argc, char **argv)
{
//Variables pour son pur
  WavData w;

  char *new_data = new char[SIZE*2];

  double audio[SIZE][2];
  double fft_out[SIZE][2];
  double long_audio_f[SIZE*2][2];
  double long_audio_t[SIZE*2][2];

//TIME-STRETCHING PUR
  for(int i=0;i<SIZE;i++){
    float t = (float)i/FREQUENCY;
    float omega = 2.0*M_PI*LA;

    audio[i][0]=AMPLITUDE*(sin(omega*t)+1);
    audio[i][1]=0;
  }

  fft(N, audio, fft_out);

  for(int i=0;i<SIZE;i++){
    int x = i;
    int y = 2*x;

    long_audio_f[y][0]=fft_out[x][0];
    long_audio_f[y+1][0]=fft_out[x][0];
    long_audio_f[y][1]=0;
    long_audio_f[y+1][1]=0;
  }

 ifft(N*2, long_audio_t, long_audio_f);

 for(int i=0;i<SIZE*2;i++){
   new_data[i] = long_audio_t[i][0];
 }

 w.setAudioFormat(1); //1 pour pcm
 w.setNbrChanel(1); // 2 canaux car stéréo
 w.setFrequency(FREQUENCY); //fréquence d'échantillage
 w.setBytePerSec(FREQUENCY); //= freq
 w.setBytePerBloc(1); // 1 octets par bloc
 w.setBitsPerSample(8); // 8 bits par échantillon (car 1 octet)
 w.clearData();
 w.setDatasize(SIZE*2);
 w.setData(new_data);
 w.save("TIME_STRETCHING_PUR.WAV");
}
