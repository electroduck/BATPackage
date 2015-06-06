// USAGE: pad.exe <file> <size> [pad with]

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	BYTE pad_byte = 0;
	long int pad_size;
	LARGE_INTEGER file_size;
	DWORD file_pos;
	DWORD file_pos_old;
	BYTE* padding;
	void* file;
	LPOFSTRUCT junk;

	if(argc < 3) {
		puts("Error: Please specify file and target size.");
		return 1;
	}
	pad_size = strtol(argv[2], NULL, 0);
	if(argc >= 4)
		pad_byte = (BYTE)strtol(argv[3], NULL, 0);

	file = CreateFile(argv[1], GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(!file) {
		puts("Error: Cannot open file.");
		return 1;
	}
	if(!GetFileSizeEx(file, &file_size)) {
		puts("Error: Unable to get size of file.");
		return 1;
	}
	pad_size -= file_size.QuadPart;
	if(pad_size < 0) {
		puts("Warning: File is already larger than target.");
		return 2;
	}

	file_pos = SetFilePointer(file, 0, 0, FILE_END);
	file_pos_old = file_pos;
	padding = malloc(pad_size);
	memset(padding, pad_byte, pad_size);
	if(!WriteFile(file, padding, pad_size, &file_pos, NULL)) {
		puts("Error: Failed to write file.");
		return 1;
	}
	if((file_pos-file_pos_old) == 0) {
		puts("Warning: No bytes written.");
		return 2;
	}

	puts("OK.");
	return 0;
}
