#include "functions.h"

int isnumber(char *text){
  for(int i = 0; i < strlen(text); i++){
    if(i == 0 && text[i] == '\n'){
      return False;
    }
    if(!isdigit(text[i]) && text[i] != '\n'){
      return False;
    }
  }
  return True;
}

int strcut(char *str, int begin, int len){
  int lentgh = (int)strlen(str);

  if (len < 0) len = lentgh - begin;
  if (begin + len > lentgh) len = lentgh - begin;
  memmove(str + begin, str + begin + len, lentgh - len + 1);

  return len;
}

const char* truncate(char *string, int limit){
  if(strlen(string) > limit){
    strcut(string, limit-2, -1);
    strcat(string, "...");
  }

  return string;
}

void readString(char *string, int maxInputSize){
  fgets(string, maxInputSize, stdin);
  removeNewline(string);
}

void readInt(int *n, int maxInputSize){
  char tempString[50];
  fgets(tempString, maxInputSize, stdin);
  *n = atoi(tempString);
}

void readFloat(float *n, int maxInputSize){
  char tempString[50];
  fgets(tempString, maxInputSize, stdin);
  *n = atof(tempString);
}

void removeNewline(char *string){
  string[strcspn(string, "\n")] = 0;
}
