#include "functions.h"
#include <stdio.h>
#include <string.h>

extern int maxEquipmentId;
extern Equipamento equipamento[256];
extern Apps app[256];
extern int maxAppId;

//Devides an already valid date into 3 ints
boolean insertDate(char *dateStr, int *date){
  if(isValidDate(dateStr)) {
    sscanf(dateStr, "%d/%d/%d", &date[0], &date[1], &date[2]);
    return True;
  }

  return False;
}
 
void insertType(int id){
  char temp[20];
  int tempInt;

  //while the user's option is not valid (1 or 2)ask continously
  renderColor("1 - Computador; 2 - Servidor\n", GREEN);
  renderColor("Tipo de dispositivo: ", GREEN);
  do {
    clearToLineEnd();
    readInt(&equipamento[id].type, 20);
    if (equipamento[id].type < 1 || equipamento[id].type > 2) {
      showInvalidOption();
    } 
  } while(equipamento[id].type < 1 || equipamento[id].type > 2);
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

  equipamento[id].data.dia = date[0];
  equipamento[id].data.mes = date[1];
  equipamento[id].data.ano = date[2];
}

void insertCpuName(int id){
  clearToLineEnd();
  renderColor("Nome: ", GREEN);
  readString(equipamento[id].cpu.name, 50);
}

void insertCpuClock(int id){
  clearToLineEnd();
  renderColor("Clocks: ", GREEN);
  //while the user's option is not valid (between 0 and 10,exlusive)ask continously
  do {
    readFloat(&equipamento[id].cpu.clock, 20);
    if (equipamento[id].cpu.clock <= 0 || equipamento[id].cpu.clock >= 10) {
      showInvalidOption();
    }
  }while (equipamento[id].cpu.clock <= 0 || equipamento[id].cpu.clock >= 10);
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
  readString(equipamento[id].departamento, 50);
}

void insertInsurance(int id){
  //insurance start must be a positive number
  clearToLineEnd();
  renderColor("Garantia em Meses: ", GREEN);
  do {
    readInt(&equipamento[id].garantia, 20);
    if (equipamento[id].garantia < 0) {
      showInvalidOption();
    }
  }while (equipamento[id].garantia < 0);
}

void insertRam(int id){
  //while the user's option is not valid (between 0 and 1000 exlusive)ask continously
  clearToLineEnd();
  renderColor("Quantidade de RAM (GB): ", GREEN);
  do {
    readInt(&equipamento[id].ram, 10);
    if (equipamento[id].ram <= 0 || equipamento[id].ram >= 1000) {
      showInvalidOption();
    }
  }while (equipamento[id].ram <= 0 || equipamento[id].ram >= 1000);
}

void insertOS(int id){
  clearToLineEnd();
  renderColor("Sistema Operativo: ", GREEN);
  readString(equipamento[id].sistema, 50);
}

/* Disk Insert */
void insertDiskName(int id, int diskID){
  clearToLineEnd();
  renderColor("\tNome: ", GREEN);
  readString(equipamento[id].discos[diskID].name, 50);
}

void insertDiskSize(int id, int diskID){
  //while the user's option is not valid (between 0 GB and 22 TB)ask continously
  clearToLineEnd();
  renderColor("\tCapacidade: ", GREEN);
  do {
    readInt(&equipamento[id].discos[diskID].capacidade, 20);
    if (equipamento[id].discos[diskID].capacidade <= 0 || equipamento[id].discos[diskID].capacidade >= 22000) {
      showInvalidOption();
    }
  }while (equipamento[id].discos[diskID].capacidade <= 0 || equipamento[id].discos[diskID].capacidade >= 22000);
}

void insertDisk(int id){
  int ask = 1;
  do{
    moveCursor(5,0);
    clearToScreenEnd();
    renderColor("Disco:\n", GREEN);
    int diskID = equipamento[id].diskNum;
    insertDiskName(id, diskID);
    insertDiskSize(id, diskID);
    equipamento[id].diskNum++;

    if(!askConfirmation("Adicionar outro")) ask = 0;
  }while(ask != 0);
}

/* Network Board Insert */
int uniqueIp(const int ip[4]){
  int strikes = 0;

  for (int equipment = 0;  equipment <= maxEquipmentId; equipment++) {
    for (int card = 0; card <= equipamento[equipment].networkCardNum; card++) {
      for (int i = 0; i < 4; i++) {
        if (ip[i] == equipamento[equipment].placas[card].ip[i]) {
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
    equipamento[id].placas[networkCardId].ip[i]= ip[i];
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
    equipamento[id].placas[networkCardId].mask[i]= mask[i];
  }
}

void calculateBroadcast(int id, int networkCardId){
  int ip[4], mask[4];
  for (int i = 0; i < 4; i++) {
    ip[i] = equipamento[id].placas[networkCardId].ip[i];
    mask[i] = equipamento[id].placas[networkCardId].mask[i];
    if (mask[i] == 0) {
      equipamento[id].placas[networkCardId].broadcast[i] = 255;
    }else if(mask[i] == 255){
      equipamento[id].placas[networkCardId].broadcast[i] = ip[i];
    }else{
      int multiplier = 256 - mask[i];
      int count = multiplier;
      while(ip[i] >= count){
        count += multiplier;
      }
      equipamento[id].placas[networkCardId].broadcast[i] = count-1;
    }
  }
}

void insertNetworkCard(int id){
  int ask = 1;
  do {
    moveCursor(5, 0);
    clearToScreenEnd();
    renderColor("Place de rede:\n", GREEN);
    insertIp(id, equipamento[id].networkCardNum);
    insertMask(id, equipamento[id].networkCardNum);
    calculateBroadcast(id, equipamento[id].networkCardNum);
    equipamento[id].networkCardNum++;
    if (!askConfirmation("Adicionar outra")) ask = 0;
  } while (ask != 0);
}

/* APP insert */
void insertAppVersion(int id, int appId){
  clearToLineEnd();
  renderColor("Versao da App: ", GREEN);
  readString(equipamento[id].app[appId].versao, 20);
}

void insertAppExpireDate(int id, int appId){
  int date[3];
  char tempString[20];

  //while the user's option doest not satisfy isValidDate ask continously
  clearToLineEnd();
  renderColor("Insira a validade (dd/mm/yyyy): ", GREEN);
  do {
    readString(tempString, 20);
    if (insertDate(tempString, date) == False) {
      showInvalidOption();
    }
  } while(isValidDate(tempString) == False);

  equipamento[id].app[appId].validade.dia = date[0];
  equipamento[id].app[appId].validade.mes = date[1];
  equipamento[id].app[appId].validade.ano = date[2];
}

void insertInstalledApp(int id){
  insertAppVersion(id, equipamento[id].appNum);
  insertAppExpireDate(id, equipamento[id].appNum);
  equipamento[id].appNum++;
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
      int appID = equipamento[id].appNum;
      equipamento[id].app[appID].appId = insertApp();
      insertInstalledApp(id);

      if(!askConfirmation("Adicionar mais uma")) ask = 0;
    }while(ask != 0);
  }
}

void showApps(int id){
  int ask = 1;
  if(askConfirmation("Quer adicionar uma aplicação")){
    do{
      int option = 0;
      moveCursor(5,0);
      clearToScreenEnd();
      printf("Selecione Aplicação (0 para nova)\n");
      int moveRight = 0;
      int count4by4 = 0;
      char tempString[50];
      for (int i = 0; i < maxAppId; i++) {
        rightCursor(moveRight - 1);
        strcpy(tempString, app[i].name);
        printf("%2d - %-10s\n", i + 1, truncate(tempString, 10));
        count4by4++;
        saveCursor();
        if (count4by4 == 4) {
          count4by4 = 0;
          moveRight += 18;
          if (i != maxAppId - 1) {
            upCursor(4);
          }
        }
      }

      do {
        restoreCursor();
        printf("\n> ");
        readInt(&option, 100);
        for(int appId = 0; appId < equipamento[id].appNum; appId++){
          if(equipamento[id].app[appId].appId == option-1) {
            showSpecificOption("[Aplicação já adicionada]");
            continue;
          }
        }
      }while(option < 0 || option > maxAppId);

      moveCursor(5,0);
      clearToScreenEnd();
      int appID = equipamento[id].appNum;
      if(option == 0){
        equipamento[id].app[appID].appId = insertApp();
      }else{
        equipamento[id].app[appID].appId = option-1;
      }
      insertInstalledApp(id);

      if(!askConfirmation("Adicionar mais uma")) ask = 0;
    }while(ask != 0);
  }
}

/* Extras */
void renderInstalledApps(int id){
  char tempString[500];

  printf("Aplicações %d\n", equipamento[id].appNum);
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
  int tempInt = -1;

  clear();
  renderTitle("Inserir Equipamento");

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
}
