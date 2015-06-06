
// Batch file "compiler"
// USAGE: compile.exe <batchfile> <executable>

#include <stdio.h>
#include <Windows.h>
#include <errno.h>
#include "util.h"
#include <string.h>

char* LOADER_FILENAME = "loader.exe";

// exefrombat.exe = 14 chars
#define MYNAME_LENGTH 14
#define MYDIR_BUFLEN 1024

int main(int argc, char** argv) {
	FILE* input;
	FILE* output;
	int c;
	char loader[MYDIR_BUFLEN];
	DWORD loader_len;

	if(argc < 3) {
		puts("Please specify a batch file to compile, and a name for the output executable.");
		return 1;
	}
	
	memset(loader, 0, MYDIR_BUFLEN);
	loader_len = GetModuleFileName(NULL, loader, MYDIR_BUFLEN);
	memset(loader+loader_len-MYNAME_LENGTH, 0, MYNAME_LENGTH);
	strappend(loader, LOADER_FILENAME);

	if(!CopyFile(loader, argv[2], FALSE)) {
		printf("Error %d: Unable to copy loader `%s' to `%s'.\n", GetLastError(), loader, argv[2]);
		return 1;
	}

	input = fopen(argv[1], "r");
	if(!input) {
		printf("Error %d: Unable to open input file `%s'.\n", errno, argv[1]);
		return 1;
	}

	output = fopen(argv[2], "a");
	if(!output) {
		printf("Error %d: Unable to open output file `%s'.\n", errno, argv[2]);
		return 1;
	}

	if(fseek(output, 0, SEEK_END) != 0) {
		printf("Error: Unable to seek to end of output file `%s'.\n", argv[2]);
		return 1;
	}

	while(1==1) {
		c = fgetc(input);
		if(c == EOF) {
			break;
		} else {
			fputc(c, output);
			if(ferror(output)) {
				printf("Error: Unable to write character `%c' to output file `%s'.\n", c, argv[2]);
				return 1;
			}
		}
	}

	puts("OK.");
	return 0;
}
