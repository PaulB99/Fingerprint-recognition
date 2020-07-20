/**
 * Pre-Processing of fingerprint images
 */

#include <stdio.h>
#include <stdlib.h>

void straighten(char path[]) {

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

    // Find size of image and fill a buffer with the image
    int size = height*width;
	unsigned char buffer[size],out[size];	
    fread(buffer,sizeof(unsigned char),size,fIn);

    // Copy to out buffer
    for(i=0;i<size;i++)
	{
		out[i] = buffer[i];
	}

    //write image data back to the file
    fwrite(out,sizeof(unsigned char),size,fOut);

	fclose(fIn);
	fclose(fOut);
}

void skeleton(char path[]) {

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

    // Find size of image and fill a buffer with the image
    int size = height*width;
	unsigned char buffer[size],out[size];	
    fread(buffer,sizeof(unsigned char),size,fIn);

    // Copy to out buffer
    for(i=0;i<size;i++)
	{
		out[i] = buffer[i];
	}

    //write image data back to the file
    fwrite(out,sizeof(unsigned char),size,fOut);

	fclose(fIn);
	fclose(fOut);
}