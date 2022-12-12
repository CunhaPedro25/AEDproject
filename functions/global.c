#include "functions.h"

//Devides an already valid date into 3 ints
boolean insertDate(const char *dateStr, int *date){
  if(isValidDate(dateStr)) {
    sscanf(dateStr, "%d/%d/%d", &date[0], &date[1], &date[2]);
    return True;
  }

  return False;
}

const char* currentDate(){
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  static char date[80];
  strftime(date,80,"%d/%m/%Y", tm);
  return date;
}

const char* currentHours(){
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  static char date[80];
  strftime(date,80,"%H:%M", tm);
  return date;
}

int countDigits(int number){
  int count = 0;
  do{
    number = number/10;
    count++;
  }while(number != 0 );

  return count;
}

int strcut(char *str, int begin, int len){
  int lentgh = (int)strlen_utf8(str);

  if (len < 0) len = lentgh - begin;
  if (begin + len > lentgh) len = lentgh - begin;
  memmove(str + begin, str + begin + len, lentgh - len + 1);

  return len;
}

//Makes strings shorter by cutting them at a specific limit and appending them with "..."
const char* truncate(char *string, int limit){
  if(strlen_utf8(string) > limit){
    strcut(string, limit-2, -1);
    strcat(string, "...");
  }

  return string;
}

size_t strlen_utf8(const char *string) {
  size_t count = 0;
  while (*string) {
    count += (*string++ & 0xC0) != 0x80;
  }
  return count;
}

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

//Checks for int type in string by finding char that are not digits
boolean isInt(char *text){
  for(int i = 0; i < strlen_utf8(text); i++){
    if(!isdigit(text[i])){
      return False;
    }
  }
  return True;
}

//Checks for float type in string by finding at most 1 '.' or ',' and char that are not digits
boolean isFloat(char *text){
  int strikes = 0;
  for(int i = 0; i < strlen_utf8(text); i++){
    if(!isdigit(text[i])){
      if(text[i] == '.' || text[i] == ','){
        strikes++;
        if(strikes > 1) return False;
      }else{
        return False;
      }
    }
  }
  return True;
}

//Finds if a year is leap or not 
boolean isleapYear(int y) {
   if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
      return True;
   else
      return False;
}

//Validates a date from a string in the formart (dd/mm/yyyy)
boolean isValidDate(const char *date) {
  int d, m, y;
  if ((sscanf(date, "%d/%d/%d",&d,&m,&y)) == 3) {
    //quick exit routes
    if(y < 1970)
      return False;
    if(m < 1 || m > 12)
      return 0;
    if(d < 1 || d > 31)
      return False;
    //check for february
    if( m == 2 ){
      if(isleapYear(y)) {
        if(d <= 29) return True;
      }else {
        if(d <= 28) return True;
      }
      return False;
    }
    //april, june, september and november are with 30 days
    if ( m == 4 || m == 6 || m == 9 || m == 11 ){
      if(d <= 30)
        return True;
      else
        return False;
    }
    return True;
  }
  return False;
}

//Checks for valid ip from a string formated as such (Ex:10.4.155.192)
boolean isValidIp(char *ip){
  int num1, num2, num3, num4; 
  if ((sscanf(ip, "%d.%d.%d.%d",&num1,&num2,&num3,&num4)) == 4) {
    return (num1 > 0 && num1 <= 255) && (num2 >=0 && num2 <= 255) && (num3 >=0 && num3 <= 255) && (num4 >= 0 && num4 <= 255);
  }
  return False;
}

boolean checkIfExpired(int day, int month, int year){
  int date[3];
  time_t t = time(NULL);
  struct tm today = *localtime(&t);
  date[0] = today.tm_mday;
  date[1] = today.tm_mon + 1;
  date[2] = today.tm_year + 1900;

  if(date[2] > year) return True;

  if(date[2] == year) {
    if(date[1] > month) return True;

    if(date[1] == month)
      if(date[0] >= day) return True;
  }

  return False;
}

int checkIfWarrantyExpired(int day, int month, int year, int warranty){
  for(int i = 0; i < warranty; i++){
    month++;
    if(month > 12){
      month = 0;
      year++;
    }
    if(checkIfExpired(day,month,year)){
      return warranty-(i+1);
    }
  }

  return warranty;
}

boolean isEmpty(char *text){
  if(strcmp(text, "") == 0) return True;
  for (int i = 0; i < strlen_utf8(text); ++i) {
    if(text[i] != ' '){
      return False;
    }
  }

  return True;
}

//Custom read func for strings that requires a valid input to be met
void readString(char *string, int maxInputSize){
  do {
    saveCursor();
    fgets(string, maxInputSize, stdin);
    removeNewline(string);

    if(isEmpty(string))
      showInvalidOption();
  }while (isEmpty(string));
}

//Custom read func for ints that requires a valid input to be met
void readInt(int *n, int maxInputSize){
  char tempString[50];
  char *trash;
  do {
    readString(tempString, maxInputSize);
    if (isInt(tempString) == False) {
      showInvalidOption();
    }
  }while (isInt(tempString) == False);
  *n = strtol(tempString, &trash, 10);
}

//Custom read func for ints that requires a valid input to be met
void readFloat(float *n, int maxInputSize){
  char tempString[50];
  char *trash;
  do {
    readString(tempString, maxInputSize);
    if (isFloat(tempString) == False) {
      showInvalidOption();
    }
  }while (isFloat(tempString) == False);
  *n = strtof(tempString, &trash);
}

boolean askConfirmation(char *question){
  char string[100];
  printf("%s (y/n)? ",question);
  do {
    readString(string, 100);
    if(strcmp(string, "y") != 0 && strcmp(string, "Y") != 0 && strcmp(string, "n") != 0 && strcmp(string, "N") != 0){
      showInvalidOption();
    }
  } while (strcmp(string, "y") != 0 && strcmp(string, "Y") != 0 && strcmp(string, "n") != 0 && strcmp(string, "N") != 0);

  return strcmp(string, "y") == 0 || strcmp(string, "Y") == 0;
}

void removeNewline(char *string){
  string[strcspn(string, "\n")] = 0;
}


/*-----------------*
 * Print Functions *
 *-----------------*/

void closedLine(int size, int isTop) {
  printf("%s", isTop == True ? TOP_LEFT_LINE : BOTTOM_LEFT_LINE);
  for (int i = 0; i < size-2; ++i) {
    printf(LINE);
  }
  printf("%s", isTop == True ? TOP_RIGHT_LINE : BOTTOM_RIGHT_LINE);

  printf("\n");
}

/**
 * @brief Print a line of "-" with a custom size
 *
 * @param size {int} - number of "-" to print (size of line)
 * @param breakLine {bool} - Confirm to add breakLine in the end
 */
void line(int size, int breakLine) {
  for (int i = 0; i < size; ++i) {
    printf(LINE);
  }
  if(breakLine)
    printf("\n");
}

/**
 *  @brief Print a custom title in the middle of responsive lines
 *
 * @param title {char *} - custom title
 */
void renderTitle(const char *title) {
  int titleSize = (int)(strlen_utf8(title) + strlen("/*--  --*/"));

  printf(" %s %s\n", currentDate(), currentHours());
  closedLine(titleSize, True);
  printf(TITLE_LEFT"%s"TITLE_RIGHT"\n", title);
  closedLine(titleSize, False);
}

void showSpecificInvalidOption(char *text){
  textColor(RED);
  clearToLineEnd();
  printf("%s", text);    // Show error message
  resetStyles();
  restoreCursor();
  clearToLineEnd();
}

void showInvalidOption(){
  showSpecificInvalidOption("[Opção Invalida]");
}

