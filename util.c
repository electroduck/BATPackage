#include "util.h"

void strappend(char* s, char* add) {
	int i = 0;
	s += strlen(s);
	while(*add != 0) {
		*s = *add;
		s++; add++;
	}
}
