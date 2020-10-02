#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Pixel{
	unsigned char r, g, b;
} Pixel;

typedef	struct Image{
	int width, height;
	Pixel* data;
} Image;

Image* newImage(int width, int height){
	Image* I = malloc(sizeof(Image));
	I->width = width;
	I->height = height;
	I->data = malloc(width*height*sizeof(Pixel*));
	return I;
}

void deleteImage(Image* I){
	if(I){
		free(I->data);
		free(I);
	}
}

Image* loadImage(char* file){
	int i,j, max;
	char buffer[10];
	Image* I;
	
	FILE* F = fopen(file, "r");
	if(!F) return NULL;
	fscanf(F, "%s %d %d %d", buffer, &i, &j, &max);

	I = newImage(i,j);

	for(i = 0 ; i < I->width*I->height ; i++){
		unsigned char r,g,b;
		fscanf(F, "%c%c%c", &r, &g, &b);
		I->data[i].r = r;
		I->data[i].g = g;
		I->data[i].b = b;
	}
	fclose(F);
	return I;
}

int saveImage(Image* I, char* file){
	int i;
	
	FILE* F = fopen(file, "w");
	if(!F) return -1;
	fprintf(F, "P6\n%d %d\n255", I->width, I->height);

	for(i = 0 ; i < I->width*I->height ; i++){
		fprintf(F, "%c%c%c", I->data[i].r, I->data[i].g, I->data[i].b);
	}

	fclose(F);
	return 0;
}

void GetPartChar(unsigned char x, unsigned char *a, int i){
	unsigned char mask[4] = {0x03, 0x0C, 0x30, 0xC0};
	unsigned char p = x & mask[i-1];
       	*a = p >> 2*(i-1);
}

void SetPartChar(unsigned char *x, unsigned char a, int i){
	unsigned char mask[4] = {0xFC, 0xF3, 0xCF, 0x3F};
	*x = (*x & mask[i-1])|(a<<2*(i-1));
}

void codeMessage(Image *I, char* message){
	int size = strlen(message);
	unsigned char ssize = (unsigned char)size;
	
	
	for(int i = 0; i < 4; i++){
		unsigned char bits;
		GetPartChar(ssize, &bits, i+1);
		SetPartChar(&(I->data[i].b), bits, 1); 
	}

	printf("taille stockée int : %d\n", size);
        printf("taille stockée : %hhu\n", ssize);

  	for(int i = 4; i < (size+1)*4; i++){
                unsigned char bits;
                GetPartChar(message[(i/4)-1], &bits, (i%4)+1);
                SetPartChar(&(I->data[i].b), bits, 1);
        }
}

char* decodeMessage(Image *I){
        int size = 0;
        unsigned char ssize;
     
     	for(int i = 0; i < 4; i++){
                unsigned char bits;
                GetPartChar(I->data[i].b, &bits, 1);
                SetPartChar(&ssize, bits, i+1);
        }
	
	size = (int)ssize;
	
	printf("taille lue int : %d\n", size);
	printf("taille lue : %hhu\n", ssize); 

	char* message = malloc(size*sizeof(char));

        for(int i = 4; i < (size+1)*4; i++){
                unsigned char bits;
                GetPartChar(I->data[i].b, &bits, 1);
                SetPartChar(&message[(i/4)-1], bits, i%4+1);
        }

	return message;
}


int main(){
	Image* I = loadImage("vincent.ppm");
	
	codeMessage(I, "salutation");
	
	saveImage(I, "encrypted.ppm");
	Image* ENC = loadImage("encrypted.ppm");

	char* message = decodeMessage(ENC);
	
	printf("%s\n", message);

	deleteImage(I);
	
	free(message);
	return 0;
}	
