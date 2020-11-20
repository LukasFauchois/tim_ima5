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
	fprintf(F, "P5\n%d %d\n255", I->width, I->height);

	for(i = 0 ; i < I->width*I->height ; i++){
		fprintf(F, "%c%c%c", I->data[i].r, I->data[i].g, I->data[i].b);
	}

	fclose(F);
	return 0;
}

void uniform_quantif(Image* I, int n){
	for(int i = 0 ; i < I->width*I->height ; i++){
                I->data[i].r = n*((I->data[i].r)/n);
                I->data[i].g = n*((I->data[i].g)/n);
                I->data[i].b = n*((I->data[i].b)/n);
        }	
}

int main(){
	int n = 200;

	Image* I = loadImage("vincent.pgm");

	uniform_quantif(I, n);

	saveImage(I, "vincent_comp.pgm");

	return 0;	
}	
