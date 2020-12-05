#include <iostream>
#include "wavdata.h"
#include "fft.h"
#include <math.h>


#define FREQ 22400
#define AMPLITUDE 10
#define FREQDO 261
#define FREQLA	440
#define SIZE FREQ*4


int main(int argc, char **argv)
{
//Definition variables
    int i;
	float pi=3.141592;
    double test[SIZE][2];
	double test1[SIZE][2];
	double test2[SIZE][2];
    double test3[SIZE*2][2];
    char *data = new char[SIZE];
	char *data2 = new char[SIZE];
	WavData w;

//Creation de la donnée
	for(i=0;i<SIZE;i++){
		float w=2.0*3.14*FREQLA;
		float t=(float)i/FREQ;
		data[i]=AMPLITUDE*(1+sin(w*t));

		test[i][0]=(double)data[i];
		test[i][1]=(double)data[i];
    }

//FFT
	fft(32768*4,test,test2);

//Modification dans le domaine fréquentiel
	for(i=0;i<SIZE;i+=2){
		test3[i][0]=test2[i][0];
        //printf("%lf ",test2[i][0]);
		test3[i+1][0]=test2[i][0];
		test3[i][1]=0;
        test3[i+1][1]=0;
	}

//FFT inverse
	ifft(32768*4,test1,test3);
//Récupération des données
	float moy=0.0;
	for(i=0;i<SIZE;i+=2){
		moy=+test3[i][0];
	}

	printf("%f ",moy);
	for(i=0;i<SIZE;i++){
		data2[i]=test1[i][0]*5+50;
	}
//Preapation format final
	w.setAudioFormat(1);
	w.setNbrChanel(1);
	w.setFrequency(FREQ);
	w.setBytePerBloc(4);
	w.setBytePerSec(FREQ);
	w.setBitsPerSample(8);
	w.clearData();

	w.setDatasize(SIZE);
	w.setData(data2);
	w.save("modifreq.WAV");

}
