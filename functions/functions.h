#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../ui/ui.h"
#include "../structures/equipamentos.h"

int isnumber(char *text);
int strcut(char *str, int begin, int len);
const char* truncate(char *string, int limit);
void removeNewline(char *string);
void readString(char *string,int maxInputSize);
void readInt(int *n, int maxInputSize);
void readFloat(float *n, int maxInputSize);
#endif //FUNCTIONS_H
