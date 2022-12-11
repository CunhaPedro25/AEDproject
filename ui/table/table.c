#include "table.h"

int validTableOption(char *option, int *size, int maxID){
  if(isInt(option)){
    return validNumber(option, maxID);
  }

  if(option[1] == '\0') {
    switch (option[0]) {
      case 'a':
      case 'A':
        if (*size-5 > 0) {
          *size -= (maxID == *size && maxID % 5 != 0) ? *size%5 : 5;
          return  True;
        }
        restoreCursor();
        clearToScreenEnd();
        return False;
      case 'd':
      case 'D':
        if(maxID == 0 || *size == maxID){
          restoreCursor();
          clearToScreenEnd();
          return False;
        }

        if (*size+5 <= maxID) {
          *size += 5;
          return  True;
        }else if(*size - maxID < 5){
          *size = maxID;
          return  True;
        }
        restoreCursor();
        clearToScreenEnd();
        return False;
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


int tableControls(int *size, int maxID, int lineSize){
  char option[10];
  char functionsText[2][20] = {
      " Selecionar <id> ",
      "Sair [S] "
  };
  int fucntionLineSize = 0;
  for(int i = 0; i < 2; i++){
    fucntionLineSize += (int)strlen_utf8(functionsText[i]);
  }
  lineSize = lineSize < fucntionLineSize ? fucntionLineSize : lineSize;
  int spacesBetween = 0;

  moveCursor(13,0);

  line(lineSize, True);

  /* Render fucntions for table */
  for(int i = 0; i < 2; i++){
    printf("%s", functionsText[i]);

    if(i != 1) {
      int extraText = (int) (strlen_utf8(functionsText[i]) + strlen(functionsText[i+1]));
      spacesBetween = lineSize - extraText;
      for (int j = 0; j < spacesBetween; j++) {
        printf(" ");
      }
    }
  }

  /* Page Control */
  printf("\n%s", *size-5 > 0 ? LEFT_ARROW" A " : GROUP_LINES);
  lineSize -= (int)strlen("-----")*2;
  line(lineSize,False);
  printf("%s\n", *size+5 <= maxID || *size != maxID ? " D "RIGHT_ARROW : GROUP_LINES);

  printf("\n"PROMPT);
  saveCursor();
  do{
    readString(option, 10);
  }while(!validTableOption(option, size, maxID));

  if((option[0] == 's' || option[0] == 'S')){
    return 0;
  }

  /* Check if it's a number and return its value if true (0 - MaxID) */
  if(isInt(option)) {
    return validNumber(option, maxID);
  }

  return -1;  // The return value is -1 to not break the while loop from the original fucntion (0 - leave menu)
}

extern int maxAppId;
extern int maxEquipmentId;
extern Apps app[256];
extern Equipment equipment[256];

void aplicacoesTable(){
  int option = -1;
  int size = maxAppId < 5 ? maxAppId : 5;

  do {
    clear();
    renderTitle("Tabela de Aplicações");

    char *keys = " id |      Nome      |        Designação      ";

    int tableSize = (int)strlen_utf8(keys);

    line(tableSize+2,True);
    printf(VLINE"%s"VLINE"\n", keys);
    line(tableSize+2,True);

    if(maxAppId > 0){
      char tempString[200];
      int startingSize = (size-5 < 0 ? 0 : (size == maxAppId && (maxAppId % 5) != 0 ? size-(maxAppId % 5) : size-5));
      for(int i = startingSize; i < size; i++){
        printf("| %2d ", i+1);
        strcpy(tempString,app[i].name);
        printf("|  %-12s  ", truncate(tempString, 10));
        strcpy(tempString,app[i].descricao);
        printf("|  %-20s  ", truncate(tempString, 18));
        printf("|\n");
      }
      line(tableSize+2,True);
    }else{
      rightCursor(tableSize/2 - (int)(strlen_utf8("Sem Aplicações")/2));
      printf("Sem Aplicações\n");
    }

    option = tableControls(&size, maxAppId, tableSize);

    if(option >= 1 && option <= maxAppId){
      appPage(option-1);
    }
  } while (option != 0);
}


void equipamentosTable(){
  int option;
  int size = maxEquipmentId < 5 ? maxEquipmentId : 5;

  do {
    clear();
    renderTitle("Tabela de Equipamentos");

    char *keys = " id |    TIPO    |  Data DD/MM/YY  |  Garantia  |      CPU      /  GHz   |    RAM   |      DISCO      /  Tamanho  " ;
    int tableSize = (int)strlen_utf8(keys) + 2;

    line(tableSize,True);
    printf(VLINE"%s"VLINE"\n", keys);
    line(tableSize,True);
    if(maxEquipmentId > 0){
      char temp[100];
      int startingSize = (size-5 < 0 ? 0 : (size == maxEquipmentId && (maxEquipmentId % 5) != 0 ? size-(maxEquipmentId % 5) : size-5));
      for(int i = startingSize; i < size; i++){
        printf("| %2d ", i+1);
        printf("|  %s%-5s  ", equipment[i].type == 1 ? "   " : "", equipment[i].type == 1 ? "PC" : "SERVIDOR");


        printf("|    %02d/%02d/%04d   |", equipment[i].data.day, equipment[i].data.month, equipment[i].data.year);

        if(equipment[i].warranty < 1000){
          equipment[i].warranty <= 1 ? textColor(RED) : equipment[i].warranty <= 5 ? textColor(YELLOW) : textColor(DEFAULT);
          printf(" %3d Mes%-2s  ", equipment[i].warranty, equipment[i].warranty == 1 || equipment[i].warranty == -1 ? "" : "es");
          resetStyles();
        }else{
          printf("  LIFETIME  ");
        }

        strcpy(temp, equipment[i].cpu.name);
        printf("|  %-12s ", truncate(temp, 11));
        printf("/  %.2f  ", equipment[i].cpu.clock);

        printf("|  %3d GB  ", equipment[i].ram);

        if(equipment[i].diskNum == 1) {
          int capacity = equipment[i].disk[0].capacidade;
          strcpy(temp, equipment[i].disk[0].name);
          printf("|  %-13s  ", truncate(temp, 12));
          printf("/   %3d %s  ", (capacity >= 1000? capacity/1000 : capacity), (capacity >= 1000? "TB" : "GB"));
        }else{
          printf("|  %2d Disks ( Selecione id ) ", equipment[i].diskNum);
        }

        printf("|\n");
      }
      line(tableSize, True);
    }else{
      rightCursor(tableSize/2 - (int)(strlen_utf8("Sem equipamentos")/2));
      printf("Sem equipamentos\n");
    }

    option = tableControls(&size, maxEquipmentId, tableSize);
    if(option >= 1 && option <= maxEquipmentId){
      equipamentPage(option-1);
    }
  } while (option != 0);
}