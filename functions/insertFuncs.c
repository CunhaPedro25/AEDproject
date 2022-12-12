#include "functions.h"
#include <stdio.h>
#include <string.h>

extern int maxEquipmentId;
extern Equipment equipment[256];
extern Apps app[256];
extern int maxAppId;
 
void insertType(int id){
  char temp[20];
  int tempInt;

  //while the user's option is not valid (1 or 2)ask continously
  renderColor("1 - Computador; 2 - Servidor\n", GREEN);
  renderColor("Tipo de dispositivo: ", GREEN);
  do {
    clearToLineEnd();
    readInt(&equipment[id].type, 20);
    if (equipment[id].type < 1 || equipment[id].type > 2) {
      showInvalidOption();
    } 
  } while(equipment[id].type < 1 || equipment[id].type > 2);
}

void insertAquisitionDate(int id){
  int date[3];
  char tempString[20];

  //while the user's option doest not satisfy isValidDate ask continously
  clearToLineEnd();
  renderColor("Data de Aquisição (dd/mm/yyyy ou Data de Hoje [h]): ", GREEN);
  do {
    readString(tempString, 20);
    if (strcmp(tempString, "Hoje") == False
        || strcmp(tempString, "hoje") == False
        || strcmp(tempString, "H") == False
        || strcmp(tempString, "h") == False) {
      strcpy(tempString, currentDate());
    }

    if (insertDate(tempString, date) == False) {
      showInvalidOption();
    }
  } while(isValidDate(tempString) == False);

  equipment[id].data.day = date[0];
  equipment[id].data.month = date[1];
  equipment[id].data.year = date[2];
}

void insertCpuName(int id){
  clearToLineEnd();
  renderColor("Nome: ", GREEN);
  readString(equipment[id].cpu.name, 50);
}

void insertCpuClock(int id){
  clearToLineEnd();
  renderColor("Clocks: ", GREEN);
  //while the user's option is not valid (between 0 and 10,exlusive)ask continously
  do {
    readFloat(&equipment[id].cpu.clock, 20);
    if (equipment[id].cpu.clock <= 0 || equipment[id].cpu.clock >= 10) {
      showInvalidOption();
    }
  }while (equipment[id].cpu.clock <= 0 || equipment[id].cpu.clock >= 10);
}

void insertCpu(int id){
  clearToLineEnd();
  renderColor("CPU:\n", GREEN);
  printf("    ");
  insertCpuName(id);
  printf("    ");
  insertCpuClock(id);
}

void insertDepartament(int id){
  clearToLineEnd();
  renderColor("Departamento: ", GREEN);
  readString(equipment[id].department, 50);
}

void insertInsurance(int id){
  //insurance start must be a positive number
  clearToLineEnd();
  renderColor("Garantia em Meses: ", GREEN);
  do {
    readInt(&equipment[id].warranty, 20);
    if (equipment[id].warranty < 0) {
      showInvalidOption();
    }
  }while (equipment[id].warranty < 0);
}

void insertRam(int id){
  //while the user's option is not valid (between 0 and 1000 exlusive)ask continously
  clearToLineEnd();
  renderColor("Quantidade de RAM (GB): ", GREEN);
  do {
    readInt(&equipment[id].ram, 10);
    if (equipment[id].ram <= 0 || equipment[id].ram >= 1000) {
      showInvalidOption();
    }
  }while (equipment[id].ram <= 0 || equipment[id].ram >= 1000);
}

void insertOS(int id){
  clearToLineEnd();
  renderColor("Sistema Operativo: ", GREEN);
  readString(equipment[id].operatingSystem, 50);
}

/* Disk Insert */
void insertDiskName(int id, int diskID){
  clearToLineEnd();
  renderColor("\tNome: ", GREEN);
  readString(equipment[id].disk[diskID].name, 50);
}

void insertDiskSize(int id, int diskID){
  //while the user's option is not valid (between 0 GB and 22 TB)ask continously
  clearToLineEnd();
  renderColor("\tCapacidade (GB): ", GREEN);
  do {
    readInt(&equipment[id].disk[diskID].capacidade, 20);
    if (equipment[id].disk[diskID].capacidade <= 0 || equipment[id].disk[diskID].capacidade >= 22000) {
      showInvalidOption();
    }
  }while (equipment[id].disk[diskID].capacidade <= 0 || equipment[id].disk[diskID].capacidade >= 22000);
}

void insertDisk(int id){
  int ask = 1;
  do{
    moveCursor(5,0);
    clearToScreenEnd();
    renderColor("Disco:\n", GREEN);
    int diskID = equipment[id].diskNum;
    insertDiskName(id, diskID);
    insertDiskSize(id, diskID);
    equipment[id].diskNum++;

    if(!askConfirmation("Adicionar outro")) ask = 0;
  }while(ask != 0);
}

/* Network Board Insert */
int uniqueIp(const int ip[4]){
  int strikes = 0;

  for (int id = 0;  id <= maxEquipmentId; id++) {
    for (int card = 0; card <= equipment[id].networkCardNum; card++) {
      for (int i = 0; i < 4; i++) {
        if (ip[i] == equipment[id].networkCard[card].ip[i]) {
          strikes++;
          if (strikes == 4) {
            return False;
          }
        }
      }
      strikes = 0;
    }
  }
  return True;
}

void insertIp(int id, int networkCardId){
  char tempString[20];
  int ip[4];
  //while the user's input doest not satisfy isValidIp ask continously
  clearToLineEnd();
  renderColor("\tEndereço IP: ", GREEN);
  do {
    readString(tempString, 20);
    if (isValidIp(tempString) == False) {
      showInvalidOption();
    }else {
      sscanf(tempString,"%d.%d.%d.%d", &ip[0],&ip[1],&ip[2],&ip[3]);
      if (uniqueIp(ip) == False) {
        showInvalidOption();
      }
    }
  } while(isValidIp(tempString) == False || uniqueIp(ip) == False);
  // assign the ip values to the struct of id
  for (int i = 0; i < 4; i++) {
    equipment[id].networkCard[networkCardId].ip[i]= ip[i];
  }
}

void insertMask(int id, int networkCardId){
  char tempString[20];
  int mask[4];
  //while the user's input doest not satisfy isValidIp ask continously
  clearToLineEnd();
  renderColor("\tMascara: ", GREEN);
  do {
    readString(tempString, 20);
    if (isValidIp(tempString) == False) {
      showInvalidOption();
    }
  } while(isValidIp(tempString) == False);
  // assign the mask values to the struct of id
  sscanf(tempString,"%d.%d.%d.%d", &mask[0],&mask[1],&mask[2],&mask[3]);
  for (int i = 0; i < 4; i++) {
    equipment[id].networkCard[networkCardId].mask[i]= mask[i];
  }
}

void calculateBroadcast(int id, int networkCardId){
  int ip[4], mask[4];
  for (int i = 0; i < 4; i++) {
    ip[i] = equipment[id].networkCard[networkCardId].ip[i];
    mask[i] = equipment[id].networkCard[networkCardId].mask[i];
    if (mask[i] == 0) {
      equipment[id].networkCard[networkCardId].broadcast[i] = 255;
    }else if(mask[i] == 255){
      equipment[id].networkCard[networkCardId].broadcast[i] = ip[i];
    }else{
      int multiplier = 256 - mask[i];
      int count = multiplier;
      while(ip[i] >= count){
        count += multiplier;
      }
      equipment[id].networkCard[networkCardId].broadcast[i] = count - 1;
    }
  }
}

void insertNetworkCard(int id){
  int ask = 1;
  do {
    moveCursor(5, 0);
    clearToScreenEnd();
    renderColor("Placa de rede:\n", GREEN);
    insertIp(id, equipment[id].networkCardNum);
    insertMask(id, equipment[id].networkCardNum);
    calculateBroadcast(id, equipment[id].networkCardNum);
    equipment[id].networkCardNum++;
    if (!askConfirmation("Adicionar outra")) ask = 0;
  } while (ask != 0);
}

/* APP insert */
void insertAppVersion(int id, int appId){
  clearToLineEnd();
  renderColor("Versao da App: ", GREEN);
  readString(equipment[id].app[appId].version, 20);
}

void insertAppExpireDate(int id, int appId){
  int date[3];
  char tempString[20];

  //while the user's option doest not satisfy isValidDate ask continously
  clearToLineEnd();
  renderColor("Insira a license (dd/mm/yyyy): ", GREEN);
  do {
    readString(tempString, 20);
    if (insertDate(tempString, date) == False) {
      showInvalidOption();
    }
  } while(isValidDate(tempString) == False);

  equipment[id].app[appId].license.day = date[0];
  equipment[id].app[appId].license.months = date[1];
  equipment[id].app[appId].license.year = date[2];
}

void insertInstalledApp(int id){
  insertAppVersion(id, equipment[id].appNum);
  insertAppExpireDate(id, equipment[id].appNum);
  equipment[id].appNum++;
}

void insertAppName(int id){
  clearToLineEnd();
  renderColor("Nome da aplicaçao: ", GREEN);
  readString(app[id].name, 50);
}

void insertAppDescripton(int id){
  clearToLineEnd();
  renderColor("Breve descriçao: ", GREEN);
  readString(app[id].descricao, 100);
}

int insertApp(){
  insertAppName(maxAppId);
  insertAppDescripton(maxAppId);
  int appID = maxAppId;
  maxAppId++;
  return appID;
}

void askNewApp(int id){
  int ask = 1;
  if(askConfirmation("Sem aplicações predifinidas. Deseja Adicionar uma")){
    do{
      moveCursor(5,0);
      clearToScreenEnd();
      int appID = equipment[id].appNum;
      equipment[id].app[appID].appId = insertApp();
      insertInstalledApp(id);

      if(!askConfirmation("Adicionar mais uma")) ask = 0;
    }while(ask != 0);
  }
}

void showApps(int id){
  if(askConfirmation("Quer adicionar uma aplicação")){
    int ask;
    do{
      ask = True;
      int option = 0;
      moveCursor(5,0);
      clearToScreenEnd();
      printf("Selecione Aplicação (Nova App [0]; Sair [s])\n");
      int moveRight = 0;
      int count4by4 = 0;
      char tempString[50];
      for (int i = 0; i < maxAppId; i++) {
        rightCursor(moveRight - 1);
        strcpy(tempString, app[i].name);
        printf("%2d - %-10s\n", i + 1, truncate(tempString, 10));
        count4by4++;
        if (count4by4 == 4) {
          count4by4 = 0;
          moveRight += 18;
          if (i != maxAppId - 1) {
            upCursor(4);
          }
        }
      }

      int invalid = False;
      char string[100];
      moveCursor(10,0);
      printf("\n> ");
      do {
        readString(string, 100);
        if(strcmp(string, "s") == 0 || strcmp(string, "S") == 0){
          invalid = False;
        }else{
          if(!isInt(string)){
            invalid = True;
            showInvalidOption();
          }else{
            char *trash;
            option = strtol(string, &trash, 10);
            if(option != 0){
              for(int appId = 0; appId <= equipment[id].appNum; appId++){
                if(equipment[id].app[appId].appId == option - 1 && equipment[id].appNum != 0) {
                  invalid = True;
                  showSpecificInvalidOption("[Aplicação já adicionada]");
                }
              }
            }
            if(option < 0 || option > maxAppId){
              invalid = True;
              showInvalidOption();
            }
          }
        }
      }while(invalid);
      if(strcmp(string, "s") == 0 || strcmp(string, "S") == 0){
        ask = False;
      }

      if(ask){
        moveCursor(5,0);
        clearToScreenEnd();
        int appID = equipment[id].appNum;
        if(option == 0){
          equipment[id].app[appID].appId = insertApp();
        }else{
          equipment[id].app[appID].appId = option - 1;
        }
        insertInstalledApp(id);

        if(!askConfirmation("Adicionar mais uma")) ask = False;
      }
    }while(ask);
  }
}

/* Extras */
void renderInstalledApps(int id){
  char tempString[500];

  printf("Aplicações %d\n", equipment[id].appNum);
  int moveRight = 0;
  int count4by4 = 0;
  if(equipment[id].appNum > 0) {
    for (int i = 0; i < equipment[id].appNum; i++) {
      rightCursor(moveRight - 1);
      strcpy(tempString, app[equipment[id].app[i].appId].name);
      printf("%2d - %-10s %s", i + 1, truncate(tempString, 10), equipment[id].app[i].version);
      if(checkIfExpired(equipment[id].app[i].license.day, equipment[id].app[i].license.months, equipment[id].app[i].license.year)){
        renderColor(" EXPIRADO \n", RED);
      }else {
        printf(" %02d/%02d/%04d\n", equipment[id].app[i].license.day, equipment[id].app[i].license.months,
               equipment[id].app[i].license.year);
      }

      count4by4++;
      if (count4by4 == 4) {
        count4by4 = 0;
        moveRight += 34;
        if (i != equipment[id].appNum - 1)
          upCursor(4);
      }
    }
  }else{
    printf("Sem Aplicações instaladas\n");
  }
}

/* Main Insert */
void insertNewApp(){
  clear();
  renderTitle("Inserir Aplicações");

  insertApp();
}

void insertEquipment(){

  clear();
  renderTitle("Inserir Equipamento");
  if(maxEquipmentId <= 254){
    int tempInt = -1;

    insertType(maxEquipmentId);
    insertAquisitionDate(maxEquipmentId);
    insertDepartament(maxEquipmentId);
    insertInsurance(maxEquipmentId);
    insertCpu(maxEquipmentId);
    insertRam(maxEquipmentId);
    insertOS(maxEquipmentId);

    if(askConfirmation("Adicionar Disco")) {
      insertDisk(maxEquipmentId);
    }

    if(askConfirmation("Adicionar uma placa de rede")) {
      insertNetworkCard(maxEquipmentId);
    }

    if(maxAppId > 0){
      showApps(maxEquipmentId);
    }else{
      askNewApp(maxEquipmentId);
    }

    maxEquipmentId++;
  }else{
    printf("Maximo de equipamentos\n");
    char temporary[10];
    do {
      readString(temporary, 10);
    } while (strcmp(temporary, "s") == 0 || strcmp(temporary, "S") == 0);
  }

}
