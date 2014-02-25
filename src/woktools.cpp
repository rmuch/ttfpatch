/*
	woktools.c

	Some helper routines

	(C) Wolfram Esser, 4.2.1999
*/


#include <stdlib.h>
#include <stdio.h>


void fatal_error(char* message, int status)
{
	fprintf (stderr, "***FATAL ERROR: %s\n", message);
	exit(status);
}


void writeLE4(signed long value, FILE* outFile)		// little-endian: Intel-style, 4 byte
{
	unsigned char raw[4];

	raw[0] = (char) (value & 0xFF);
	value = value >> 8;
	raw[1] = (char) (value & 0xFF);
	value = value >> 8;
	raw[2] = (char) (value & 0xFF);
	value = value >> 8;
	raw[3] = (char) (value & 0xFF);

	fwrite(raw, 1, 4, outFile);
}


void writeLE2(signed long value, FILE* outFile)		// little-endian: Intel-style, 2 byte
{
	unsigned char raw[2];

	raw[0] = (char) (value & 0xFF);
	value = value >> 8;
	raw[1] = (char) (value & 0xFF);

	fwrite(raw, 1, 2, outFile);
}


void writeBE4(signed long value, FILE* outFile)		// big-endian: RISC-style, 4 byte
{
	unsigned char raw[4];

	raw[3] = (char) (value & 0xFF);
	value = value >> 8;
	raw[2] = (char) (value & 0xFF);
	value = value >> 8;
	raw[1] = (char) (value & 0xFF);
	value = value >> 8;
	raw[0] = (char) (value & 0xFF);

	fwrite(raw, 1, 4, outFile);
}


void writeBE2(signed long value, FILE* outFile)		// big-endian: RISC-style, 2 byte
{
	unsigned char raw[2];

	raw[1] = (char) (value & 0xFF);
	value = value >> 8;
	raw[0] = (char) (value & 0xFF);

	fwrite(raw, 1, 2, outFile);
}


// ****************************************************************************************************

unsigned long readLE4(FILE* inFile)				// little-Endian: Intel-style, 4 byte
{
	unsigned long retval;
	unsigned char raw[4];
	fread(raw, 1, 4, inFile);

	retval = ((unsigned long)raw[3]<<24) 
		| ((unsigned long)raw[2]<<16) 
		| ((unsigned long)raw[1]<<8) 
		| ((unsigned long)raw[0]);
	return retval;
}

unsigned long readLE2(FILE* inFile)				// little-endian: Intel-style, 2 byte
{
	unsigned long retval;
	unsigned char raw[2];
	fread(raw, 1, 2, inFile);

	retval = ((unsigned long)raw[1]<<8) 
		| ((unsigned long)raw[0]);
	return retval;
}


unsigned long readBE4(FILE* inFile)				// big-Endian: RISC-style, 4 byte
{
	unsigned long retval;
	unsigned char raw[4];
	fread(raw, 1, 4, inFile);

	retval = ((unsigned long)raw[0]<<24) 
		| ((unsigned long)raw[1]<<16) 
		| ((unsigned long)raw[2]<<8) 
		| ((unsigned long)raw[3]);
	return retval;
}

unsigned long readBE2(FILE* inFile)				// big-endian: RISC-style, 2 byte
{
	unsigned long retval;
	unsigned char raw[2];
	fread(raw, 1, 2, inFile);

	retval = ((unsigned long)raw[0]<<8) 
		| ((unsigned long)raw[1]);
	return retval;
}

