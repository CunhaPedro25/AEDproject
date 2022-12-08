#include "functions.h"

int isnumber(char *text){
  for(int i = 0; i < strlen(text); i++){
    if(i == 0 && text[i] == '\n'){
      return 0;
    }
    if(!isdigit(text[i]) && text[i] != '\n'){
      return 0;
    }
  }
  return 1;
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
