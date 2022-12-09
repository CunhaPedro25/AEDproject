#include "table.h"

extern int maxAppId;
extern int maxEquipmentId;
extern Equipamento equipamento[256];

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

int validOption(char *option, int *size, int maxID){
  if(isnumber(option)){
    return validNumber(option, maxID);
  }

  if(option[1] == '\n') {
    switch (option[0]) {
      case 'a':
      case 'A':
        if (*size-5 > 0) {
          *size -= maxID == *size ? *size%5 : 5;
          return  True;
        }
        restoreCursor();
        clearToScreenEnd();
        return False;
      case 'd':
      case 'D':
        if (*size+5 <= maxID) {
          *size += 5;
          return  True;
        }else{
          if(*size - maxID < 5) {
            *size = maxID;
            return  True;
          }
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


int controls(int *size, int maxID, int lineSize){
  char option[10];
  char functionsText[2][20] = {
      " Selecionar <id> ",
      "Sair [S] "
  };
  int fucntionLineSize = 0;
  for(int i = 0; i < 2; i++){
    fucntionLineSize += (int)strlen(functionsText[i]);
  }
  lineSize = lineSize < fucntionLineSize ? fucntionLineSize : lineSize;
  int spacesBetween = 0;

  printf("\n\n");
  line(lineSize, 1);

  /* Render fucntions for table */
  for(int i = 0; i < 2; i++){
    printf("%s", functionsText[i]);

    if(i != 1) {
      int extraText = (int) (strlen(functionsText[i]) + strlen(functionsText[i+1]));
      spacesBetween = lineSize - extraText;
      for (int j = 0; j < spacesBetween; j++) {
        printf(" ");
      }
    }
  }

  /* Page Control */
  printf("\n%s", *size-5 > 0 ? "<- A " : "-----");
  lineSize -= (int)strlen("-----")*2;
  line(lineSize,0);
  printf("%s\n", *size+5 <= maxID || *size != maxID ? " D ->" : "-----");

  printf("\n❯ ");
  saveCursor();
  do{
    fgets(option, 10, stdin);
    fflush(stdin);
  }while(!validOption(option, size, maxID));

  if((option[0] == 's' || option[0] == 'S') && option[1] == '\n'){
    return 0;
  }

  /* Check if it's a number and return its value if true (0 - MaxID) */
  if(isnumber(option)) {
    return validNumber(option, maxID);
  }

  return -1;  // The return value is -1 to not break the while loop from the original fucntion (0 - leave menu)
}

void aplicacoesTable(){
  int option = -1;
  int size = maxAppId < 5 ? maxAppId : 5;

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

    option = controls(&size, maxAppId, tableSize);
  } while (option != 0);
}


void equipamentosTable(){
  int option = -1;
  int size = maxEquipmentId < 5 ? maxEquipmentId : 5;

  do {
    clear();
    renderTitle("Tabela de Equipamentos");

    char *keys = "| id |    TIPO    |  Data DD/MM/YY  |  Garantia  |      CPU      /  GHz   |    RAM   |      DISCO      /  GB  |";
    int tableSize = (int)strlen(keys);

    line(tableSize,1);
    printf("%s\n", keys);
    line(tableSize,1);
    if(maxEquipmentId > 0){
      char temp[100];
      int startingSize = (size-5 < 0 ? 0 : (size == maxEquipmentId ? size-(maxEquipmentId % 5) : size-5));
      for(int i = startingSize; i < size; i++){
        printf("| %2d ", i+1);
        printf("|  %s%-5s  ", equipamento[i].type == 1 ? "   " : "", equipamento[i].type == 1 ? "PC" : "SERVIDOR");


        printf("|   %02d/%02d/%-6d  |", equipamento[i].data.dia, equipamento[i].data.mes, equipamento[i].data.ano);

        equipamento[i].garantia <= 1 ? textColor(RED) : equipamento[i].garantia <= 5 ? textColor(YELLOW) : textColor(DEFAULT);
        printf(" %3d Mes%-2s  ", equipamento[i].garantia, equipamento[i].garantia == 1 || equipamento[i].garantia == -1  ? "" : "es");
        resetStyles();

        strcpy(temp, equipamento[i].cpu.name);
        printf("|  %-12s ", truncate(temp, 11));
        printf("/  %.2f  ", equipamento[i].cpu.clock);

        printf("|  %3d GB  ", equipamento[i].ram);

        if(equipamento[i].diskNum == 1) {
          strcpy(temp, equipamento[i].discos[0].name);
          printf("|  %-13s  ", truncate(temp, 13));
          printf("/  %2d  ", equipamento[i].discos[0].capacidade);
        }else{
          printf("|  %2d Discos (Selecione) ", equipamento[i].diskNum);
        }

        printf("|\n");
      }
    }else{
      rightCursor(tableSize/2 - (int)(strlen("Sem equipamentos")/2));
      printf("Sem equipamentos");
    }

    option = controls(&size, maxEquipmentId, tableSize);
  } while (option != 0);
}