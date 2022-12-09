#include "functions.h"
#include <string.h>

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

int isInt(char *text){
  for(int i = 0; i < strlen(text); i++){
    if(!isdigit(text[i])){
      return False;
    }
  }
  return True;
}

int isFloat(char *text){
  int strikes = 0;
  for(int i = 0; i < strlen(text); i++){
    if(!isdigit(text[i])){
      if(text[i] == '.' || text[i] == ','){
        strikes++;
        if(strikes > 1) return False;
      }
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
  do {
    fgets(string, maxInputSize, stdin);
    removeNewline(string);

    if(strcmp(string,"") == False)
      showInvalidOption();
  }while (strcmp(string,"") == False);
}

void readInt(int *n, int maxInputSize){
  char tempString[50];
  char *trash;
  do {
  fgets(tempString, maxInputSize, stdin);
  removeNewline(tempString);
  }while (isInt(tempString) == False);
  *n = strtol(tempString, &trash, 10);
}

void readFloat(float *n, int maxInputSize){
  char tempString[50];
  char *trash;
  do {
  fgets(tempString, maxInputSize, stdin);
  removeNewline(tempString);
  }while (isFloat(tempString) == False);
  *n = strtof(tempString, &trash);
}

void removeNewline(char *string){
  string[strcspn(string, "\n")] = 0;
}

int isleapYear(int y) {
   if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
      return True;
   else
      return False;
}
int datevalid(int d, int m, int y) {
  //Quick exit routes
  if(y < 1970)
    return False;
  if(m < 1 || m > 12)
    return 0;
  if(d < 1 || d > 31)
    return False;
  //Check for february
  if( m == 2 ){
    if(isleapYear(y)) {
      if(d <= 29)
        return True;
      else
        return False;
    }
  }
  //April, June, September and November are with 30 days
  if ( m == 4 || m == 6 || m == 9 || m == 11 ){
    if(d <= 30)
      return True;
    else
      return False;
  }
  
  return True;
}
