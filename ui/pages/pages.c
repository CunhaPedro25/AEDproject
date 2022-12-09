#include "pages.h"

int validPagesOption(char *option, int *id, int maxID){
  if(isInt(option)){
    return validNumber(option, maxID);
  }

  if(option[1] == '\0') {
    switch (option[0]) {
      /*Previous Page*/
      case 'a':
      case 'A':
        if (*id-1 > 0) {
          *id -= 1;
          return  True;
        }
        restoreCursor();
        clearToScreenEnd();
        return False;
      /*Next Page*/
      case 'd':
      case 'D':
        if (*id+1 < maxID) {
          *id += 1;
          return  True;
        }
        restoreCursor();
        clearToScreenEnd();
        return False;
      /*Edit*/
      case 'e':
      case 'E':
      /*Remove*/
      case 'r':
      case 'R':
      /*Leave*/
      case 's':
      case 'S':
        return True;

      default:
        break;
    }
  }

  showInvalidOption();
  return False;
}

int pageControls(int *id, int maxID){
  char option[10];

  char *functions = " Editar [E]  Eliminar [R]  Outro <id>  Sair [S] ";
  int lineSize = (int) strlen(functions);

  /* Render fucntions for table */
  printf("\n\n");
  line(lineSize, 1);
  printf("%s", functions);

  /* Page Control */
  printf("\n%s", *id-1 > 0 ? "<- A " : "-----");
  lineSize -= (int)strlen("-----")*2;
  line(lineSize,0);
  printf("%s\n", *id+1 < maxID ? " D ->" : "-----");

  printf("\n❯ ");
  saveCursor();
  do{
    readString(option, 10);
  }while(!validPagesOption(option, id, maxID));

  if((option[0] == 's' || option[0] == 'S')){
    return 0;
  }

  /* Check if it's a number and return its value if true (0 - MaxID) */
  if(isInt(option)) {
    return validNumber(option, maxID);
  }

  return -1;  // The return value is -1 to not break the while loop from the original fucntion (0 - leave menu)
}


extern int maxEquipmentId;

void equipamentPage(int id){
  int option;

  do{
    clear();
    printf("%d", id+1);

    option = pageControls(&id, maxEquipmentId);

    if(option >= 1 && option <= maxEquipmentId)
      id = option;
  } while (option != 0);
}