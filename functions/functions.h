#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../ui/ui.h"

int isnumber(char *text);
void removeNewline(char *string);
void readString(char *string,int maxInputSize);
void readInt(int *n, int maxInputSize);
void readFloat(float *n, int maxInputSize);
#endif //FUNCTIONS_H
