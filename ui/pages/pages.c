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
  printf("\n%s", *id-1 >= 0 ? "<- A " : "-----");
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

extern Equipamento equipamento[256];
extern int maxEquipmentId;
extern int maxAppId;
extern int maxNetworkCardId;

void equipamentPage(int id){
  int option;
  char tempString[500];
  char tempDiskSize[2] = "";

  do{
    clear();
    renderTitle("Pagina de Equipamento");

    printf("Equipamento %d\n", id+1);

    printf("Tipo -> %-8s", equipamento[id].type == 1 ? "PC" : "Servidor");

    rightCursor(19);
    strcpy(tempString, equipamento[id].sistema);
    printf("|  Sistema Operativo -> %s\n", truncate(tempString, 10));

    strcpy(tempString, equipamento[id].cpu.name);
    printf("CPU -> %-14s %.2f GB",  truncate(tempString, 12), equipamento[id].cpu.clock);

    rightCursor(6);
    printf("|  RAM -> %d GB\n", equipamento[id].ram);

    /* Render Disks */
    if(equipamento[id].diskNum > 1) {
      printf("Número de Discos: %d\n", equipamento[id].diskNum);
      line(33, 1);
      printf("|      Name     /   Capacidade  |\n");
      line(33, 1);
      for (int i = 0; i < equipamento[id].diskNum; i++){
        strcpy(tempString, equipamento[id].discos[i].name);
        strcpy(tempDiskSize, (equipamento[id].discos[i].capacidade >= 1000 ? "TB" : "GB"));
        equipamento[id].discos[i].capacidade = equipamento[id].discos[i].capacidade >= 1000 ? equipamento[id].discos[i].capacidade/1000 : equipamento[id].discos[i].capacidade;
        printf("|  %-11s  /    %4d %s    |\n", truncate(equipamento[id].discos[i].name, 11), equipamento[id].discos[0].capacidade, tempDiskSize);
      }
      line(33, 1);
    }else{
      strcpy(tempString, equipamento[id].discos[0].name);
      strcpy(tempDiskSize, (equipamento[id].discos[0].capacidade >= 1000 ? "TB" : "GB"));
      equipamento[id].discos[0].capacidade = equipamento[id].discos[0].capacidade >= 1000 ? equipamento[id].discos[0].capacidade/1000 : equipamento[id].discos[0].capacidade;
      printf("Disco -> %-14s %d %s\n",  truncate(equipamento[id].discos[0].name, 12), equipamento[id].discos[0].capacidade, tempDiskSize);
    }

    /* Render List of Installed Apps */
    saveCursor();
    printf("\nAplicações\n");
    int moveRight = 0;
    int count4by4 = 0;
    for(int i = 0; i < equipamento[id].appNum; i++){
      rightCursor(moveRight-1);
      strcpy(equipamento[id].app[i].versao, "v1.1");
      strcpy(tempString, "12345678901");
      printf("%2d - %-10s %s", i+1, truncate(tempString, 10), equipamento[id].app[i].versao);
      printf(" %02d/%02d/%04d\n", equipamento[id].app[i].validade.dia, equipamento[id].app[i].validade.mes, equipamento[id].app[i].validade.ano);

      count4by4++;
      if(count4by4 == 4){
        count4by4 = 0;
        moveRight += 34;
        if(i != equipamento[id].appNum-1)
          upCursor(4);
      }
    }
    restoreCursor();
    downCursor(6);

    /* Network table */
    saveCursor();
    moveCursor(7, 36);
    printf("|  Placas\n");
    rightCursor(35);
    printf("|  ");
    line(37,1);
    rightCursor(35);
    printf("|  |    IP     |   MASK    | BROADCAST |\n");

    rightCursor(35);
    printf("|  ");
    line(37,1);
    for (int i = 0; i < equipamento[id].networkCardNum; i++) {
      rightCursor(35);
      printf("|  |  ");
      for(int ip = 0; ip < 4; ip++){
        printf("%d", equipamento[0].placas[i].ip[ip]);
        if(ip < 3){
          printf(".");
        }
      }
      printf("  |  ");
      for(int ip = 0; ip < 4; ip++){
        printf("%d", equipamento[0].placas[i].mask[ip]);
        if(ip < 3){
          printf(".");
        }
      }
      printf("  |  ");
      for(int ip = 0; ip < 4; ip++){
        printf("%d", equipamento[0].placas[i].broadcast[ip]);
        if(ip < 3){
          printf(".");
        }
      }
      printf("  |  \n");
    }
    rightCursor(35);
    printf("|  ");
    line(37,1);

    restoreCursor();


    option = pageControls(&id, maxEquipmentId);

    if(option >= 1 && option <= maxEquipmentId)
      id = option;
  } while (option != 0);
}