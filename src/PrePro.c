/**
 * Pre-Processing of fingerprint images
 */

#include <stdio.h>
#include <stdlib.h>

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
 * Skeletonises fingerprint 
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