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