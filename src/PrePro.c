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
	
	/**
	 * 
	 * SKELETONISE IMAGE
	 * 
	 */

	unsigned char buffer2[size];
	buffer2 = skeletonise(buffer, height, width);

	// Write to output
	fwrite(buffer,sizeof(unsigned char),size,fOut);

	fclose(fIn);
	fclose(fOut);
}

/**
 * Zhang-Suen skeletonisation algorithm
 */
char* skeletonise(char* img, int height, int width) {
	bool changed = true;
	int a;
	int b;
	int size = height * width;
	int i, j;
	char* neigh;
	char* newimg = img;
	while(changed) {

		changed = false;

		// First criteria
    	for(i = 0; i > size; i++) {
			neigh = neighbours(img, height, width, i);

			// Define a and b 
			a = changedneighbours(neigh);
			b = blackneighbours(neigh);
			
			// First criteria
			bool crit1 = false;
			bool crit2 = false;
			bool crit3 = false;
			bool crit4 = false;
			bool crit5 = false;

			if(img[i] == BLACK && length(neigh) == 8) {
				crit1 = true;
			}
			if(b >= 2 && b<= 6) {
				crit2 = true;
			}
			if(a == 1) {
				crit3 = true;
			}
			if(neigh[0] == WHITE || neigh[2] == WHITE || neigh[4] == WHITE) {
				crit4 = true;
			}
			if(neigh[2] == WHITE || neigh[4] == WHITE || neigh[6] == WHITE) {
				crit5 = true;
			}

			// Set to white
			if(crit1 && crit2 && crit3 && crit4 && crit5) {
				newimg[i] = WHITE;
				changed = true;
			}
		}

		// Set image
		img = newimg;

		// Second criteria
		for(j=0; j > size; j++) {
			neigh = neighbours(img, height, width, j);

			// Define a and b 
			a = changedneighbours(neigh);
			b = blackneighbours(neigh);
			
			// Criteria
			bool crit6 = false;
			bool crit7 = false;
			bool crit8 = false;
			bool crit9 = false;
			bool crit10 = false;

			if(img[i] == BLACK && length(neigh) == 8) {
				crit6 = true;
			}
			if(b >= 2 && b<= 6) {
				crit7 = true;
			}
			if(a == 1) {
				crit8 = true;
			}
			if(neigh[0] == WHITE || neigh[2] == WHITE || neigh[6] == WHITE) {
				crit9 = true;
			}
			if(neigh[0] == WHITE || neigh[4] == WHITE || neigh[6] == WHITE) {
				crit10 = true;
			}

			// Set to white
			if(crit6 && crit7 && crit8 && crit9 && crit10) {
				newimg[i] = WHITE;
				changed = true;
			}
		}

		// Set image
		img = newimg;
    }

	return img;
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

/**
 * The number of switches from black to white in the list of neighbours (with an extra one at the end to make it circular)
 */
int changedneighbours(char* list) {
	int i;
	char x;
	char y;
	int result = 0;
	for(i=1; i<9; i++) {
		x = list[i-1];
		y = list[i % 7];
		if(x != y) {
			result++;
		}
	}
	return result;
}

/**
 * The number of black neighbours in the list
 */
int blackneighbours(char* list) {
	int i;
	int result = 0;
	for(i=0; i<8; i++) {
		if list[i] == BLACK {
			result++;
		}
	}
}

int main() {
	run("../data/sample.bmp");
	return 0;
}


