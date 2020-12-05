#include <iostream>
#include "../wavdata.h"
#include "../fft.h"
#include <math.h>

#include <fstream>
using namespace std;

#define FREQUENCY 44100
#define SIZE FREQUENCY*2
#define AMPLITUDE 50
#define LA 440

int main(int argc, char **argv)
{
  WavData w;
  ofstream file;

  file.open("pur.csv", ios::app); //ouverture du tableur

	char *data = new char[SIZE];

	int i;
  for(i=0;i<SIZE;i++){
    float t = (i*1.0)/FREQUENCY;
    float omega = 2.0*M_PI*LA;
    data[i]=AMPLITUDE*(sin(omega*t)+1);
    string line = to_string(t) + ";" + to_string((int)data[i]);
    file << line << endl; //écriture des valeurs dans le tableur
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

  file.close(); //fermeture du tableur
	w.save("PUR.WAV");

  return 0;
}
