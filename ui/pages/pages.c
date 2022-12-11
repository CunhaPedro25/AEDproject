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
    if (askConfirmation("Quer mesmo eliminar"))
      return -1;    // Code to detect that its in deleteing menu
  }

  if((strcmp(option, "e") == 0 || strcmp(option, "e") == 0) && maxID > 0){
    return -2;    // Code to detect that its in edit menu
  }

  /* Check if it's a number and return its value if true (0 - MaxID) */
  if(isInt(option)) {
    return validNumber(option, maxID);
  }

  return -10;  // The return value is -10 to not break the while loop from the original fucntion (0 - leave menu)
}

extern Apps app[256];
extern Equipment equipment[256];
extern int maxEquipmentId;
extern int maxAppId;

void appPage(int id){
  int option;

  do{
    clear();
    renderTitle("Página de Aplicações");

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
          for(int appID = 0; appID < equipment[equipmentID].appNum; appID++){
            if(equipment[equipmentID].app[appID].appId == id){
              countInstallation++;
              rightCursor(moveRight - 1);
              printf("Equipment %-2d - %s", equipmentID + 1, equipment[equipmentID].app[appID].version);
              printf(" %02d/%02d/%04d\n", equipment[equipmentID].app[appID].license.day, equipment[equipmentID].app[appID].license.months, equipment[equipmentID].app[appID].license.year);

              count++;
              saveCursor();
              if (count == 6) {
                count= 0;
                moveRight += 31;
                if (equipmentID != maxEquipmentId - 1) {
                  upCursor(6);
                }
              }
            }
          }
        }

        if(countInstallation == 0){
          printf("Sem instalações\n");
        }else{
          restoreCursor();
        }
      }else{
        printf("Sem Equipamentos\n");
      }
    }else{
      printf("Sem Aplicações\n");
    }

    option = pageControls(&id, maxAppId);

    if(option == -1) {
      deleteApps(id);
      option = 0;
    }

    if(option == -2) {
      editApps(id);
    }

    if(option >= 1 && option <= maxAppId)
      id = option-1;
  } while (option != 0);
}

int getTotalDiskSpace(int id){
  int totalCapacity = 0;
  for (int i = 0; i < equipment[id].diskNum; i++){
    totalCapacity += equipment[id].disk[i].capacidade;
  }

  return totalCapacity;
}

void renderInstalledDisks(int id){
  char tempString[500];
  int capacity = 0;

  if(equipment[id].diskNum > 1) {
    int totalCapacity = getTotalDiskSpace(id) >= 1000 ? getTotalDiskSpace(id)/1000 : getTotalDiskSpace(id);
    printf("%d Discos; Total: %d %s\n", equipment[id].diskNum, totalCapacity, (getTotalDiskSpace(id) >= 1000 ? "TB" : "GB"));
    line(33, True);
    printf("|      Name     /   Capacidade  |\n");
    line(33, True);
    for (int i = 0; i < equipment[id].diskNum; i++){
      strcpy(tempString, equipment[id].disk[i].name);
      capacity = equipment[id].disk[i].capacidade >= 1000 ? equipment[id].disk[i].capacidade / 1000 : equipment[id].disk[i].capacidade;
      printf("|  %-11s  /    %4d ", truncate(tempString, 11), capacity);
      printf("%s    |\n", (equipment[id].disk[i].capacidade >= 1000 ? "TB" : "GB"));
    }
    line(33, True);
  }else if(equipment[id].diskNum == 1){
    strcpy(tempString, equipment[id].disk[0].name);
    capacity = equipment[id].disk[0].capacidade >= 1000 ? equipment[id].disk[0].capacidade / 1000 : equipment[id].disk[0].capacidade;
    printf("Disco:\n");
    printf("    Nome: %-14s\n", truncate(equipment[id].disk[0].name, 12));
    printf("    Capacidade: %d ", capacity);
    printf("%s\n", (equipment[id].disk[0].capacidade >= 1000 ? "TB" : "GB"));
  }else{
    printf("Sem Discos\n");
  }
  saveCursor();
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
  int moveRight = 39;
  moveCursor(9, moveRight);
  printf(VLINE"  Placas\n");
  rightCursor(moveRight-1);
  printf(VLINE"  ");
  char *keys = "|         IP        |        MASK       |     BROADCAST     |";
  int tableSize = (int)strlen_utf8(keys);
  line(tableSize,True);
  rightCursor(moveRight-1);
  printf(VLINE"  %s\n", keys);
  rightCursor(moveRight-1);
  printf(VLINE"  ");
  line(tableSize,True);

  if(equipment[id].networkCardNum > 0) {
    for (int i = 0; i < equipment[id].networkCardNum; i++) {
      rightCursor(moveRight-1);
      printf(VLINE"  ");
      renderIpNumbers(equipment[id].networkCard[i].ip);
      renderIpNumbers(equipment[id].networkCard[i].mask);
      renderIpNumbers(equipment[id].networkCard[i].broadcast);
      printf("|\n");
    }
  }else{
    rightCursor(moveRight-1);
    printf(VLINE);
    rightCursor((tableSize/2)-2);
    printf("Sem Placas\n");
  }
  rightCursor(moveRight-1);
  printf(VLINE"  ");
  line(tableSize,True);
}

void equipamentPage(int id){
  int option;
  char tempString[500];

  do{
    clear();
    renderTitle("Página de Equipamento");

    if(maxEquipmentId > 0){
      printf("Equipment %d - %02d/%02d/%04d\n\n", id + 1, equipment[id].data.day, equipment[id].data.month, equipment[id].data.year);

      printf("Tipo: %-8s", equipment[id].type == 1 ? "PC" : "Servidor");

      rightCursor(24);
      strcpy(tempString, equipment[id].operatingSystem);
      printf(VLINE"  Sistema Operativo: %s\n", truncate(tempString, 10));

      strcpy(tempString, equipment[id].cpu.name);
      printf("CPU: %-10s %.2f GHz (%5.0f MIPS) ", truncate(tempString, 8), equipment[id].cpu.clock, (equipment[id].cpu.clock * 1250));

      printf(VLINE"  RAM -> %d GB\n", equipment[id].ram);

      /* Render Disks */
      renderInstalledDisks(id);

      /* Network table */
      renderNetworkBoards(id);

      /* Render List of Installed Apps */
      if(equipment[id].diskNum > 1)
        downCursor((equipment[id].diskNum - equipment[id].networkCardNum) - 1);
      renderInstalledApps(id);

    }else{
      printf("Sem Equipamentos\n");
    }

    option = pageControls(&id, maxEquipmentId);

    if(option == -1) {
      deleteEquipment(id);
      option = 0;
    }

    if(option == -2) {
      editEquipment(id);
    }

    if(option >= 1 && option <= maxEquipmentId)
      id = option-1;
  } while (option != 0);
}