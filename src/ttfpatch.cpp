// ttfpatch.cpp
//
// changes the fsType (16-bit, Bigendian) value of a Truetype font
// the fsType value defines, whether or not a TTF is embeddable
// a fsType of decimal 2 prohibits embedding of the font in a PDF
// a fsType of decimal 0, 4 and 8 enables the embedding of the font in a PDF
//
// 2001-02-23 by Wolfram Esser wok@derwok.de



#include "stdafx.h"
#include "woktools.h"
#include "string.h"
#include <stdlib.h>



int readheader();
void printlicencebits(unsigned short fstype);
void pause();


// globals
char* filename;
FILE* fontfile;
unsigned long tab_fsType_pos;	// offset of fsType in TTF file
unsigned short tab_fsType;	// <<<--- We will change THIS !!!
unsigned long ttf_filesize;
char* ttf_allbytes;



int main(int argc, char* argv[])
{
	unsigned short wanted_fsType;
	 filename = argv[1];

	printf("\n\nTTFPATCH v1.0 - (C) by Wolfram Esser [wok@derwok.de] 2001-02-23\n");


	if (argc != 2 && argc != 3)	// usage
	{
		printf("Provides an easy way for font designers to set the 'embeddable' flags\n");
		printf("of their own true type fonts. If you want to prohibit embedding of your\n");
		printf("font e.g. in Acrobat PDF files, simply run: 'ttfpatch myfont.ttf 2'\n\n");
		printf ("Usage: ttfpatch TrueTypeFontFile [NewFsTypeValue]\n");
		printf ("\n");
		printf ("fsType values:\n");
		printf ("       0: embedding for permanent installation\n");
		printf ("       1: reserved - do not use!\n");
		printf ("       2: embedding restricted (not allowed!)\n");
		printf ("       4: embedding for preview & printing allowed\n");
		printf ("       8: embedding for editing allowed\n");

		pause();
		return 1;
	}


	fontfile = fopen(filename, "rb");	// open font for analysis
	if(! fontfile)
	{
		printf ("\nError: Could not open fontfile '%s' for reading\n", filename);
		pause();
		return 1;
	}

	printf ("\n");
	printf ("- Opened: '%s'\n", filename);
	if (readheader())							// now read the header and find value and position of fsType
	{
		fclose(fontfile);
		pause();
		return 1;	
	}

	if(argc == 3)	//  user wants to change fsType
	{
		wanted_fsType = atoi(argv[2]);
		printf ("- Wanted fsType: hex:'%04x'\n", wanted_fsType);
		printlicencebits((unsigned short)wanted_fsType);

		if(wanted_fsType & 0x0001)	// allowed bit combination?
		{
			printf ("\nError: fsType & 0x0001 bit is reserved. must be zero!\n");
			fclose(fontfile);
			pause();
			return 1;
		}

		// allowed bit combination?
		if((wanted_fsType & 0x0002) && ((wanted_fsType & 0x0004) || (wanted_fsType & 0x0008)))
		{
			printf ("\nError: fsType & 0x0002 bit set, and (embedding allowed 0x0004 or 0x0008)\n");
			fclose(fontfile);
			pause();
			return 1;
		}

		// anything to change???
		if(wanted_fsType == tab_fsType)
		{
			printf ("\nNothing to do... wanted fsType %d already stored in TTF file!\n", wanted_fsType);
			fclose(fontfile);
			pause();
			return 1;
		}


		// OK - now read the WHOLE TTF file into memory
		printf ("- TTF filesize: '%d' bytes\n", ttf_filesize);

		fseek(fontfile, 0, SEEK_SET);				// rewind
		ttf_allbytes = new char[ttf_filesize];		// get memory to hold the fonts bytes
		if(! ttf_allbytes)
		{
			printf("\nError: Internal error: could not get enough memory for file\n");
			fclose(fontfile);
			pause();
			return 1;
		}

		// now read all the bytes
		unsigned long bytesread = fread(ttf_allbytes, 1, ttf_filesize, fontfile);

		if(bytesread != ttf_filesize)
		{
			printf ("\nError: Could not read %d bytes from fontfile (read: %d)\n", ttf_filesize, bytesread);
			fclose(fontfile);
			pause();
			return 1;
		}
		printf("- OK: read: '%d' bytes from file\n", bytesread);

		// now store the new value
		char* Pwanted_fsType = (char*) (&wanted_fsType);
		ttf_allbytes[tab_fsType_pos+1] = *Pwanted_fsType;	// swap bytes for big-endian!
		ttf_allbytes[tab_fsType_pos] = *(Pwanted_fsType+1);

		// reopen file - now for writing!!!
		fclose(fontfile);
		fontfile = fopen(filename, "wb");
		if(! fontfile)
		{
			printf ("\nError: Could not open fontfile '%s' for reading\n", filename);
			pause();
			return 1;
		}
		unsigned long byteswritten = fwrite(ttf_allbytes, 1, ttf_filesize, fontfile);

		if(byteswritten != ttf_filesize)
		{
			printf ("\nError: Could not write %d bytes to fontfile (written: %d)\n", ttf_filesize, byteswritten);
			fclose(fontfile);
			pause();
			return 1;
		}
		printf("- OK: written: '%d' bytes to file\n", byteswritten);
	}
	else
	{
		printf("\nNothing changed! - No new fsType value specified\n");
		printf("Run program without any arguments to get usage hints\n");
	}


	pause();
	return 0;
}





// reads the TTF header, seraches for the table with table tag 'OS/2'
// fseeks to that table and reads the fsType value (16 bit, Big-Ednian Motorola style) from there
// remembers file-position of fsType start
int readheader()
{
	unsigned long dummy;

	unsigned long version;		// Global Data
	unsigned long numtables;

	char tabtag[5];				// Table Position
	unsigned long taboffset;

	unsigned short tabversion;	// must be 0x0001

	version = readBE4(fontfile);
	printf ("- Fileformat version: hex: '%08x'\n", version);
	if (version != 0x00010000)
	{
		printf ("\nError: Fileformat version must be '0x00010000'\n");
		return 1;
	}

	numtables = readBE2(fontfile);
	printf ("- Number of Infotables: %d\n", numtables);
	if (numtables <= 9)
	{
		printf ("\nError: numtables must be greater than '9'\n");
		return 1;
	}

	dummy = readBE2(fontfile);	// search range - not needed
	dummy = readBE2(fontfile);	// entry selector - not needed
	dummy = readBE2(fontfile);	// range shift - not needed
	
	int found_os2_table = 0;
	unsigned long tables_checked = 0;
	while (tables_checked < numtables && !found_os2_table)
	{
		fread (tabtag, 4, 1, fontfile);	// read the table-name (we look for 'OS/2')
		tabtag[4] = '\0';
		dummy = readBE4(fontfile);	// checksum - not needed
		taboffset = readBE4(fontfile);	// we need THIS!
		dummy = readBE4(fontfile);	// length - not needed

		if (strcmp(tabtag, "OS/2") == 0)
		{
			printf ("- Found 'OS/2' table\n");
			found_os2_table = 1;
		}
		tables_checked ++;
	}

	printf ("- Tableoffset: hex:'%08x'\n", taboffset);
	fseek(fontfile, taboffset, SEEK_SET);				// Jump to OS/2 table
	tabversion = (unsigned short) readBE2(fontfile);	// 0x0001 Version
	if(tabversion != 0x0001)
	{
		if((tabversion == 0x0000) || (tabversion == 0x0002))
		{
			printf ("\nWarning: OS/2 tableversion is not '0x0001' but '0x0000'\n");
		}
		else
		{
			printf ("\nError: OS/2 tableversion must be 0, 1 or 2 and is hex:%04x\n", tabversion);
			return 1;
		}
	}

	dummy = readBE2(fontfile);	// average char width - not needed
	dummy = readBE2(fontfile);	// weight class - not needed
	dummy = readBE2(fontfile);	// widht class - not needed


	tab_fsType_pos = ftell(fontfile);	// remember 0-based position of fsType (16 bit)

	/////////////////////////////
	tab_fsType = (unsigned short) readBE2(fontfile);;	// <<<--- We will change THIS !!!
	/////////////////////////////

	printf ("- Curret fsType: hex:'%04x'\n", tab_fsType);
	printlicencebits(tab_fsType);

	fseek(fontfile, 0, SEEK_END);
	ttf_filesize = ftell(fontfile);

	return 0;
}






void printlicencebits(unsigned short fstype)
{
	if (fstype == 0x0000)
		printf ("       0: embedding for permanent installation allowed\n");

	if (fstype & 0x0001 == 0x0001)
		printf ("       1: reserved - not to be used, must be zero!\n");

	if (fstype & 0x0002)
		printf ("       2: embedding restricted (not allowed, at all!)\n");

	if (fstype & 0x0004)
		printf ("       4: embedding for preview & printing allowed\n");

	if (fstype & 0x0008)
		printf ("       8: embedding for editing allowed\n");
}



void pause()
{
//	char c;
//	printf("\nHit any key...");
//	c = getc(stdin);
//	printf("\n");
}
