#include "table.h"

int maxID = 15;

int validNumber(char *option){
  int value = -1;
  char *trash;
  value = strtol(option, &trash, 10);

  if(value < 0 || value > maxID) {
    showInvalidOption();
    return -1;
  }

  return value;
}

int validLetter(char *option, int *size){
  if(isnumber(option)){
    return validNumber(option);
  }

  if(option[1] == '\n') {
    switch (option[0]) {
      case 'a':
      case 'A':
        if (*size-5 > 0) {
          *size -= 5;
          return  1;
        }
        restoreCursor();
        clearToLineEnd();
        return -1;
      case 'd':
      case 'D':
        if (*size+5 <= maxID) {
          *size += 5;
          return  1;
        }
        restoreCursor();
        clearToLineEnd();
        return -1;
      case 's':
      case 'S':
        return 1;

      default:
        break;
    }
  }

  showInvalidOption();
  return -1;
}


int controls(int *size, int lineSize){
  char option[10];
  int trashLines = strlen(" Selecionar <id>Sair [S] ");
  lineSize = lineSize < trashLines ? trashLines : lineSize;

  printf("\n\n");
  line(lineSize, 1);

  /* Options for table */
  printf("Selecionar <id> ");
  trashLines = lineSize == trashLines ? 3 : lineSize-trashLines;
  for(int i = 0; i < trashLines; i++){
    printf(" ");
  }
  printf("Sair [S] \n");

  /* Page Control */
  printf("%s", *size-5 > 0 ? "<- A " : "-----");
  lineSize -= (int)strlen("-----")*2;
  line(lineSize,0);
  printf("%s", *size+5 <= maxID ? " D ->" : "-----");

  printf("\n\n> ");
  saveCursor();
  do{
    cursorVisibility(1);
    fgets(option, 10, stdin);
    cursorVisibility(0);
    fflush(stdin);
  }while(validLetter(option, size) == -1);

  if((option[0] == 's' || option[0] == 'S') && option[1] == '\n'){
    return 0;
  }

  if(isnumber(option)) {
    return validNumber(option);
  }

  return -1;
}

void aplicacoesTable(){
  int option = -1;
  int size = maxID < 5 ? maxID : 5;

  do {
    clear();
    renderTitle("Tabela de Aplicações");

    char *keys = "| id |  Nome  |  Designação  |  Tipo  |";

    int tableSize = (int)strlen(keys);


    line(tableSize,1);
    printf("%s\n", keys);
    line(tableSize,1);
    for(int i = (size-5 < 0 ? 0 : size-5); i < size; i++){
      printf("| %2d ", i+1);
      printf("|  LOl  ");
      printf("|  LOl  ");
      printf("|  LOl  |");
      printf("\n");
    }
    printf("%d", size);

    option = controls(&size, tableSize);
  } while (option != 0);
}


void equipamentosTable(){
  int option = -1;
  int size = maxID < 5 ? maxID : 5;

  do {
    clear();
    renderTitle("Tabela de Equipamentos");

    char *keys = "| id |  CPU  |  DISCO  |  DATA  |  TESTE  |  TESTE  |  TESTE  |  TESTE  |";

    int tableSize = (int)strlen(keys);


    line(tableSize,1);
    printf("%s\n", keys);
    line(tableSize,1);
    for(int i = (size-5 < 0 ? 0 : size-5); i < size; i++){
      printf("| %2d ", i+1);
      printf("|  LOl  ");
      printf("|  LOl  ");
      printf("|  LOl  |");
      printf("\n");
    }
    printf("%d", size);

    option = controls(&size, tableSize);
  } while (option != 0);
}