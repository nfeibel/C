//HW8, Nick Feibel
//c file for decoding the bin file HW8.bin
#include "decoding.h"	//Include the header file for decoding
#include <stdio.h>		//Include for fopen/fwrite
#include <limits.h>		//Include for CHAR_BIT

/*encoding() method decodes the text file ibin[] and provides the encoding
  in txt file otxt[]*/
void decoding(char otxt[], char ibin[]){
	
	//Variables are initialized
	FILE *otxtp, *ibinp;
	char a, b, c, d;
	unsigned int num;
	int status;
	
	//Files are opened
	otxtp = fopen(otxt, "w");
	ibinp = fopen(ibin, "rb");
	
	//We check if there is at least 1 int in the ibin file
	status = fread(&num, sizeof(int), 1, ibinp);
	
	//As long as there is, we start the decryption process
	while(status != 0){
		
		//Current num is calculated by calling decryption() using num
		num = decryption(num);
		
		//The chars are unpacked using the num
		unpack(num, &a, &b, &c, &d);
		
		//As long as the chars are not EOF, they are placed in the otxt file
		if(a!= EOF){ 
			putc(a, otxtp); }
		if(b!= EOF){ 
			putc(b, otxtp); }
		if(c!= EOF){ 
			putc(c, otxtp); }
		if(d!= EOF){ 
			putc(d, otxtp);}
		
		//Then we check whether there is another int, and loop again if so
		status = fread(&num, sizeof(int), 1, ibinp);
	}
	
	//Ensure files are closed
	fclose(otxtp);
	fclose(ibinp);
	
}

//pack() returns chars through address passing using the provided num
void unpack(unsigned int num, char *a, char *b, char *c, char *d){
	
	//chars are calculated using the mask
	unsigned mask = 0xFF;
	*d = num & mask;
	
	num = num >> CHAR_BIT;
	*c = num & mask;
	
	num = num >> CHAR_BIT;
	*b = num & mask;
	
	num = num >> CHAR_BIT;
	*a = num & mask;
		
}

//encryption() decrypts the number provided a specific shift, which ours is 5
unsigned int decryption(unsigned int num){
	int shift = 5;
	unsigned int re;
	
	re = (num >> shift) | (num << (CHAR_BIT * sizeof(int) - shift));
	
	return re;
}

