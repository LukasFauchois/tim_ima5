#include <iostream>
#include "wavdata.h"
#include "fft.h"
#include <math.h>

#include <fstream>

using namespace std;

#define AMPLITUDE 10
#define PI 3.1415


int main(int argc, char **argv)
{
  WavData w;
	w.load("COW.WAV");
  ofstream file;

  file.open("pur.ods");

	char *data = w.data();

	int i;
  for(i=0;i<w.datasize();i++){
    data[i]=AMPLITUDE*(sin(440*PI*2*i)+1);
    //data2[i]='a'*i;
    printf("%d\n",data[i]);
    file << data[i] << endl;<
  }

	w.clearData();
	w.setDatasize(w.datasize());
	w.setData(data);

  file.close();
	w.save("PUR.WAV");
}
