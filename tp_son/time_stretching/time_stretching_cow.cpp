#include <iostream>
#include "../wavdata.h"
#include "../fft.h"
#include <math.h>

#include <fstream>
using namespace std;

#define FREQUENCY 22400
#define SIZE FREQUENCY*4
#define N 32768*2

int main(int argc, char **argv)
{
//Variables pour son pur
  WavData w;
  w.load("../COW.WAV");
  char *data = w.data();

  char *new_data = new char[w.datasize()*2];

  double audio[w.datasize()][2];
  double fft_out[w.datasize()][2];
  double long_audio_f[w.datasize()*2][2];
  double long_audio_t[w.datasize()*2][2];

//TIME-STRETCHING COW

  for(int i=0;i<w.datasize();i++){
    audio[i][0]=(double)data[i];
    audio[i][1]=0;//(double)data[i];
  }

  fft(N, audio, fft_out);

  for(int i=0;i<w.datasize();i+=2){
    long_audio_f[i][0]=fft_out[i][0];
    long_audio_f[i][1]=0;
  }

  for(int i=1;i<w.datasize();i+=2){
    long_audio_f[i][0]=fft_out[i][0];
    long_audio_f[i][1]=0;
  }

 ifft(N, long_audio_t, long_audio_f);

 for(int i=0;i<w.datasize();i++){
   new_data[i] = long_audio_t[i][0]*5+50;
 }


 w.setAudioFormat(1);
 w.setNbrChanel(1);
 w.setFrequency(FREQUENCY);
 w.setBytePerBloc(1);
 w.setBytePerSec(FREQUENCY);
 w.setBitsPerSample(8);
 w.clearData();
 w.setDatasize(w.datasize());
 w.setData(new_data);
 w.save("TIME_STRETCHING_COW.WAV");
}
