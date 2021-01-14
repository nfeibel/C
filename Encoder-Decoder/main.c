//HW8, Nick Feibel
//main.c file for encoding and decoding the text file HW8.txt
#include "encoding.h"	//Include header file for encoding
#include "decoding.h"	//Include header file for decoding
#include <stdlib.h>		//Include for system() method

//main() simply runs through encoding and decoding process to ensure it works
int main(){
	
	system("cat HW8.txt");				//Display text file pre encoding/decoding
	encoding("HW8.txt", "HW8.bin"); 	//Encodes the text file
	decoding("HW8c.txt", "HW8.bin");	//Decodes the bin file
	system("cat HW8c.txt");				//Display text file post encoding/decoding
	
}
