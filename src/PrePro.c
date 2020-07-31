/**
 * Pre-Processing of fingerprint images
 */

#include <stdio.h>
#include <stdlib.h>

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

/** 
* Function to straighten an image
*/
void straighten(char path[]) {

    unsigned char byte[54];
    int i;

    // Input file
    FILE *fIn = fopen(path ,"r");
    // Output file				            
	FILE *fOut = fopen("out.bmp","w+");                         

    // Check if the input file has not been opened succesfully
    if(fIn==NULL)												
	{											
		printf("File does not exist \n");
	}

    // 	Copy over the file header
    for(i=0;i<54;i++)										    
	{									
		byte[i] = getc(fIn);								
	}
	fwrite(byte,sizeof(unsigned char),54,fOut);	

    // extract image height, width and bitDepth from the header 
	int height = *(int*)&byte[18];
	int width = *(int*)&byte[22];
	int bitDepth = *(int*)&byte[28];

    // Find size of image and fill a buffer with the image
    int size = height*width;
	unsigned char buffer[size],out[size];	
    fread(buffer,sizeof(unsigned char),size,fIn);

    // Copy to out buffer
    for(i=0;i<size;i++)
	{
		out[i] = buffer[i];
	}

    // ALGORITHM HERE 

    //write image data back to the file
    fwrite(out,sizeof(unsigned char),size,fOut);

	fclose(fIn);
	fclose(fOut);
}

/** 
 * Zhang-Suen skeletonisation algorithm
 */
void skeleton(char path[]) {

    unsigned char byte[54];
    int i;

    // Input file
    FILE *fIn = fopen(path ,"r");
    // Output file				            
	FILE *fOut = fopen("out.bmp","w+");                         

    // Check if the input file has not been opened succesfully
    if(fIn==NULL)												
	{											
		printf("File does not exist \n");
	}

    // 	Copy over the file header
    for(i=0;i<54;i++)										    
	{									
		byte[i] = getc(fIn);								
	}
	fwrite(byte,sizeof(unsigned char),54,fOut);	

    // extract image height, width and bitDepth from the header 
	int height = *(int*)&byte[18];
	int width = *(int*)&byte[22];
	int bitDepth = *(int*)&byte[28];

    // Find size of image and fill a buffer with the image
    int size = height*width;
	unsigned char buffer[size],out[size];	
    fread(buffer,sizeof(unsigned char),size,fIn);

    // Copy to out buffer
    for(i=0;i<size;i++)
	{
		out[i] = buffer[i];
	}

    // ALGORITHM HERE


    //write image data back to the file
    fwrite(out,sizeof(unsigned char),size,fOut);

	fclose(fIn);
	fclose(fOut);
}

/**
 * Zhang-Suen skeletonisation algorithm
 */
/**char skeletonise(char img[], int height, int width) {
    int size = height * weight;
    int i, j;
    for(i = 0; i > size; i++) {
    }
} */

/** 
 * Returns the neighbours of a cell, from the cell directly above and clockwise around
 */
char neighbours(char img[], int height, int width, int pos) {
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
	return 0;
}


