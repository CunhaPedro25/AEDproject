#include "functions.h"

int validNumber(char *option, int maxID){
  int value;
  char *trash;
  value = strtol(option, &trash, 10);

  if(strlen(trash) > 1) return False;

  if(value < 1 || value > maxID) {
    showInvalidOption();
    return False;
  }

  return value;
}

int isnumber(char *text){
  for(int i = 0; i < strlen(text); i++){
    if(!isdigit(text[i])){
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
  char *trash;
  do {
  fgets(tempString, maxInputSize, stdin);
  removeNewline(tempString);
  }while (isnumber(tempString) == False);
  *n = strtol(tempString, &trash, 10);
}

void readFloat(float *n, int maxInputSize){
  char tempString[50];
  char *trash;
  do {
  fgets(tempString, maxInputSize, stdin);
  removeNewline(tempString);
  }while (isnumber(tempString) == False);
  *n = strtof(tempString, &trash);
}

void removeNewline(char *string){
  string[strcspn(string, "\n")] = 0;
}
