#include "util.h"

void strappend(char* s, char* add) {
	s += strlen(s);
	while(*add != 0) {
		*s = *add;
		s++; add++;
	}
}
