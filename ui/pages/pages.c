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
        if (*id-1 >= 0) {
          *id -= 1;
          return  True;
        }
        showSpecificOption("");
        return False;
      /*Next Page*/
      case 'd':
      case 'D':
        if (*id+1 < maxID) {
          *id += 1;
          return  True;
        }
        showSpecificOption("");
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
  printf("\n");
  line(lineSize, True);
  printf("%s", functions);

  /* Page Control */
  printf("\n%s", *id-1 >= 0 ? LEFT_ARROW" A " : GROUP_LINES);
  lineSize -= (int)strlen("-----")*2;
  line(lineSize,False);
  printf("%s\n", *id+1 < maxID ? " D "RIGHT_ARROW : GROUP_LINES);

  printf("\n"PROMPT);
  do{
    readString(option, 100);
  }while(!validPagesOption(option, id, maxID));

  if(strcmp(option, "s") == 0 || strcmp(option, "S") == 0){
    return 0;
  }

  if((strcmp(option, "r") == 0 || strcmp(option, "R") == 0) && maxID > 0){
    char confirm[2];
    printf("Quer mesmo eliminar (y/n)? ");
    readString(confirm, 2);
    if (strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") == 0)
      return -1;    // Code to detect that its in deleteing menu
  }


  /* Check if it's a number and return its value if true (0 - MaxID) */
  if(isInt(option)) {
    return validNumber(option, maxID);
  }

  return -10;  // The return value is -10 to not break the while loop from the original fucntion (0 - leave menu)
}

extern Apps app[256];
extern Equipamento equipamento[256];
extern int maxEquipmentId;
extern int maxAppId;

void appPage(int id){
  int option;
  char tempString[500];

  do{
    clear();
    renderTitle("Pagina de Aplicações");

    maxAppId = 1;
    if(maxAppId > 0){
      printf("Aplicação %d\n\n", id + 1);

      printf("Nome: %s\n", app[id].name);
      printf("Descrição: %s\n", app[id].descricao);


      printf("\nInstalado em:\n");
      if(maxEquipmentId > 0) {
        int moveRight = 0;
        int count = 0;
        int countInstallation = 0;

        for (int equipmentID = 0; equipmentID < maxEquipmentId; equipmentID++) {
          for(int appID = 0; appID < equipamento[equipmentID].appNum; appID++){
            if(equipamento[equipmentID].app[appID].appId == id){
              countInstallation++;
              rightCursor(moveRight - 1);
              printf("Equipamento %2d - %s", equipmentID + 1, equipamento[equipmentID].app[appID].versao);
              printf(" %02d/%02d/%04d\n", equipamento[equipmentID].app[appID].validade.dia, equipamento[equipmentID].app[appID].validade.mes, equipamento[equipmentID].app[appID].validade.ano);

              count++;
              if (count == 6) {
                count= 0;
                moveRight += 30;
                saveCursor();
                if (equipmentID != maxEquipmentId - 1)
                  upCursor(6);
              }
            }
          }
        }

        if(countInstallation == 0){
          printf("Sem instalações");
        }else{
          restoreCursor();
        }
      }else{
        printf("Sem Equipamentos");
      }
    }else{
      printf("Sem Aplicações");
    }

    option = pageControls(&id, maxAppId);

    if(option == -1) {
      deleteEquipment(id);
      option = 0;
    }

    if(option >= 1 && option <= maxAppId)
      id = option-1;
  } while (option != 0);
}

void renderInstalledDisks(int id){
  char tempString[500];
  int capacity = 0;

  if(equipamento[id].diskNum > 1) {
    printf("Número de Discos: %d\n", equipamento[id].diskNum);
    line(33, True);
    printf("|      Name     /   Capacidade  |\n");
    line(33, True);
    for (int i = 0; i < equipamento[id].diskNum; i++){
      strcpy(tempString, equipamento[id].discos[i].name);
      capacity = equipamento[id].discos[i].capacidade >= 1000 ? equipamento[id].discos[i].capacidade/1000 : equipamento[id].discos[i].capacidade;
      printf("|  %-11s  /    %4d ", truncate(tempString, 11), capacity);
      printf("%s    |\n", (equipamento[id].discos[i].capacidade >= 1000 ? "TB" : "GB"));
    }
    line(33, True);
  }else{
    strcpy(tempString, equipamento[id].discos[0].name);
    capacity = equipamento[id].discos[0].capacidade >= 1000 ? equipamento[id].discos[0].capacidade/1000 : equipamento[id].discos[0].capacidade;
    printf("Disco -> %-14s %d ",  truncate(equipamento[id].discos[0].name, 12), capacity);
    printf("%s\n", (equipamento[id].discos[0].capacidade >= 1000 ? "TB" : "GB"));
  }
  saveCursor();
}

void renderInstalledApps(int id){
  char tempString[500];

  if(equipamento[id].diskNum > 1)
    downCursor(equipamento[id].diskNum-equipamento[id].networkCardNum);

  printf("Aplicações\n");
  int moveRight = 0;
  int count4by4 = 0;
  if(equipamento[id].appNum > 0) {
    for (int i = 0; i < equipamento[id].appNum; i++) {
      rightCursor(moveRight - 1);
      strcpy(tempString, app[equipamento[id].app[i].appId].name);
      printf("%2d - %-10s %s", i + 1, truncate(tempString, 10), equipamento[id].app[i].versao);
      printf(" %02d/%02d/%04d\n", equipamento[id].app[i].validade.dia, equipamento[id].app[i].validade.mes,
             equipamento[id].app[i].validade.ano);

      count4by4++;
      if (count4by4 == 4) {
        count4by4 = 0;
        moveRight += 34;
        if (i != equipamento[id].appNum - 1)
          upCursor(4);
      }
    }
  }else{
    printf("Sem Aplicações instaladas");
  }
}

void renderIpNumbers(int number[4]){
  printf("|  ");
  int width = 0;
  for(int ip = 0; ip < 4; ip++){
    width += countDigits(number[ip]);
    printf("%d", number[ip]);
    if(ip < 3){
      printf(".");
    }
  }
  printf("%*s", 14-width, "");
}

void renderNetworkBoards(int id){
  moveCursor(9, 36);
  printf(VLINE"  Placas\n");
  rightCursor(35);
  printf(VLINE"  ");
  char *keys = "|         IP        |        MASK       |     BROADCAST     |";
  int tableSize = (int)strlen_utf8(keys);
  line(tableSize,True);
  rightCursor(35);
  printf(VLINE"  %s\n", keys);
  rightCursor(35);
  printf(VLINE"  ");
  line(tableSize,True);

  if(equipamento[id].networkCardNum > 0) {
    for (int i = 0; i < equipamento[id].networkCardNum; i++) {
      rightCursor(35);
      printf(VLINE"  ");
      renderIpNumbers(equipamento[id].placas[i].ip);
      renderIpNumbers(equipamento[id].placas[i].mask);
      renderIpNumbers(equipamento[id].placas[i].broadcast);
      printf("|\n");
    }
  }else{
    rightCursor(35);
    printf(VLINE);
    rightCursor((tableSize/2)-2);
    printf("Sem Placas\n");
  }
  rightCursor(35);
  printf(VLINE"  ");
  line(tableSize,True);
}

void equipamentPage(int id){
  int option;
  char tempString[500];

  do{
    clear();
    renderTitle("Pagina de Equipamento");

    if(maxEquipmentId > 0){
      printf("Equipamento %d\n\n", id + 1);

      printf("Tipo -> %-8s", equipamento[id].type == 1 ? "PC" : "Servidor");

      rightCursor(19);
      strcpy(tempString, equipamento[id].sistema);
      printf(VLINE"  Sistema Operativo -> %s\n", truncate(tempString, 10));

      strcpy(tempString, equipamento[id].cpu.name);
      printf("CPU -> %-14s %.2f GHz", truncate(tempString, 12), equipamento[id].cpu.clock);

      rightCursor(5);
      printf(VLINE"  RAM -> %d GB\n", equipamento[id].ram);

      /* Render Disks */
      renderInstalledDisks(id);

      /* Network table */
      renderNetworkBoards(id);

      /* Render List of Installed Apps */
      renderInstalledApps(id);

    }else{
      printf("Sem Equipamentos");
    }

    option = pageControls(&id, maxEquipmentId);

    if(option == -1) {
      deleteEquipment(id);
      option = 0;
    }

    if(option >= 1 && option <= maxEquipmentId)
      id = option-1;
  } while (option != 0);
}