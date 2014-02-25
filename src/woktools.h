/*
	woktools.h

	Some helper routines

	(C) Wolfram Esser, 4.2.1999
*/

fatal_error(char* message, int status);

writeLE4(unsigned long value, FILE* outFile);		// little-endian: Intel-style, 4 byte
writeLE2(unsigned long value, FILE* outFile);		// little-endian: Intel-style, 2 byte

writeBE4(unsigned long value, FILE* outFile);		// big-endian: RISC-style, 4 byte
writeBE2(unsigned long value, FILE* outFile);		// big-endian: RISC-style, 2 byte


unsigned long readLE4(FILE* inFile);				// little-Endian: Intel-style, 4 byte
unsigned long readLE2(FILE* inFile);				// little-endian: Intel-style, 2 byte

unsigned long readBE4(FILE* inFile);				// big-Endian: RISC-style, 4 byte
unsigned long readBE2(FILE* inFile);				// big-endian: RISC-style, 2 byte



