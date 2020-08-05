/**
 * Pre-Processing of fingerprint images
 */

#include <stdio.h>
#include <stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0


/**
 * A function to relate the neighbour positions
 */
int findpos (int t[]) {
	int x;
	x = t[0] + (3 * t[1]); // Add both values and multiply the second by 3, producing unique values
	switch(x) {
		case -3 : // 0,1
			return 1;
        case -2 : // 1,-1
	        return 2;
        case 1 : // 1,0
	        return 3;
        case 4 : // 1,1
	        return 4;
        case 3 : // 0,1
	        return 5;
        case 2 :// -1,1
	        return 6;
        case -1 :// -1,0
	        return 7;
        case -4 :// -1,-1
	        return 8;
	}
}


void run(char* path){

	// Input and output files
	FILE *fIn = fopen(path,"r");
	FILE *fOut = fopen("out.bmp","w+");		       

	int i;
	unsigned char byte[54];								
	unsigned char colourTable[1024];					

	//Check file has been opened
	if(fIn==NULL)	
	{										
		printf("File does not exist\n");
	}

	//Read header
	for(i=0;i<54;i++)								
	{									
		byte[i]=getc(fIn);								
	}

	// Write header
	fwrite(byte,sizeof(unsigned char),54,fOut);	

	// Extract image height, width and bitDepth from imageHeader 
	int height = *(int*)&byte[18];
	int width = *(int*)&byte[22];
	int bitDepth = *(int*)&byte[28];

	printf("width: %d\n",width);
	printf("height: %d\n",height );

	int size=height*width;							

	/** 
	 * 
	 * BINARISE IMAGE
	 * Uses THRESHOLD to determine black/white
	 * 
	 */
	// Extract colour table
	if(bitDepth<=8)										
	{
		fread(colourTable,sizeof(unsigned char),1024,fIn);
		fwrite(colourTable,sizeof(unsigned char),1024,fOut);
	}

	// Read to buffer 
	unsigned char buffer[size];	
	fread(buffer,sizeof(unsigned char),size,fIn);


	// Determine back/white
	for(i=0;i<size;i++)	
		{
			buffer[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;
		}
	
	// Write to output
	fwrite(buffer,sizeof(unsigned char),size,fOut);

	fclose(fIn);
	fclose(fOut);
}

/**
 * Zhang-Suen skeletonisation algorithm
 */
char* skeletonise(char* img, int height, int width) {
	int a;
	int b;
    int size = height * weight;
    int i, j;
	char*
    for(i = 0; i > size; i++) {
		neigh = neighbours(img, height, width, i);
		a = 0;
		for(j=0;)
    }
}

/** 
 * Returns the neighbours of a cell, from the cell directly above and clockwise around
 */
char* neighbours(char* img, int height, int width, int pos) {
    char neigh[8];
    int i, j;
    int size = height * width;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
	        int arr[] = {i, j};
            if (i == 0 && j == 0) { // Skip central case
                continue;
            }
            else if(pos-i<0 || pos+i>size-1 || pos+(j*width)>size-1 || pos-(j*width)<0) {
                neigh[findpos(arr)] = NULL;
            }
            else {
                neigh[findpos(arr)] = pos + i + (j*width);
            }

        }
    } 
	return neigh;
}

int main() {
	run("../data/sample.bmp");
	return 0;
}


