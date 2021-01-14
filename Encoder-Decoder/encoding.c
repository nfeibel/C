//HW8, Nick Feibel
//c file for encoding the text file HW8.txt
#include "encoding.h"	//Include the header file for encoding
#include <stdio.h>		//Include for fopen/fwrite
#include <limits.h>		//Include for CHAR_BIT

/*encoding() method encodes the text file itxt[] and provides the encoding
  in bin file obin[]*/
void encoding(char itxt[], char obin[]){
	
	//Variables are initialized
	FILE *itxtp, *obinp;
	char a, b, c, d;
	unsigned int num;
	
	//Files are opened
	itxtp = fopen(itxt, "r");
	obinp = fopen(obin, "wb");
	
	//Do loop is done to ensure it goes through at least 1 iteration
	do{
		
		//Characters are taken from the file, 4 at a time
		a = getc(itxtp);
		b = getc(itxtp);
		c = getc(itxtp);
		d = getc(itxtp);
		
		//The characters are then packed and encrypted
		num = pack(a, b, c, d);
		num = encryption(num);
		
		//Then the num is written to the bin file
		fwrite(&num, sizeof(int), 1, obinp);
		
	}while(d != EOF); //Once the loop reaches EOF, it stops
	
	//Then we ensure the files are closed
	fclose(itxtp);
	fclose(obinp);
	
}

//pack() returns an unsigned int after packing the chars provided
unsigned int pack(char a, char b, char c, char d){
	
	//Return value initialized
	unsigned int re = a;
	
	//Chars are packed into re
	re = (re << CHAR_BIT) | b;
	re = (re << CHAR_BIT) | c;
	re = (re << CHAR_BIT) | d;
	
	return re;
}

//encryption() encrypts the number provided a specific shift, which ours is 5
unsigned int encryption(unsigned int num){
	
	//Shift initialized and return value initialized
	int shift = 5;
	unsigned int re;
	
	//re is calculated by using num and the shift
	re = (num << shift) | (num >> (CHAR_BIT * sizeof(int) - shift));
	
	return re;
}

