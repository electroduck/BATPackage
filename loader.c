// Batch file loader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include "util.h"

char* SPACE = " ";
char* ALTERNATE_FILE = "_loader.exe";

int main(int argc, char** argv) {
	char bf_filename[50] = "SCRIPT[0].BAT";
	int bf_location = 40000;
	FILE* output;
	FILE* self;
	int c;
	char cmd_line[32768];
	int i = 1;

	//argv[0] = ALTERNATE_FILE; // has to be used when debugging due to issue with debugger

	// Add a loop to detect if default bf_filename (SCRIPT[0].BAT) already exists.
	// If true : loop until a SCRIPT[%d].BAT is available to write.
	output = fopen(bf_filename, "r");
	while(output!=NULL) {
		snprintf(bf_filename, sizeof bf_filename, "SCRIPT[%d].BAT", i);
		output = fopen(bf_filename, "r");
		i++;
	}
	fclose(output);
	// End
	
	memcpy(cmd_line, bf_filename, strlen(bf_filename));
	i = 1;
	while(i < argc) {
		strappend(cmd_line, SPACE);
		strappend(cmd_line, argv[i]);
		i++;
	}

	self = fopen(argv[0], "r");
	output = fopen(bf_filename, "w");
	fseek(self, bf_location, SEEK_SET);
	while(1==1) {
		c = fgetc(self);
		if(c == EOF)
			break;
		else
			fputc(c, output);
	}
	fclose(output);
	fclose(self);

	system(cmd_line);

	SetLastError(0);
	if(!DeleteFile(bf_filename)) {
		printf("Unable to clean up - Error code 0x%X\n", GetLastError());
		return 1;
	}

	return 0;
}
