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
  printf("Insira o tipo de dispositivo\n");
  printf("1 - Computador; 2 - Servidor\n");
  renderColor("Tipo de dispositivo -> ", GREEN);
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
  renderColor("Data de Aquisição (dd/mm/yyyy ou Data de Hoje [h]) -> ", GREEN);
  do {
    readString(tempString, 20);
    if (strcmp(tempString, "Hoje") == False
        || strcmp(tempString, "hoje") == False
        || strcmp(tempString, "H") == False
        || strcmp(tempString, "h") == False) {
      strcpy(tempString, currentDate());
    }
    insertDate(tempString, date);
    if (isValidDate(tempString) == False) {
      showInvalidOption();
    }
  } while(isValidDate(tempString) == False);

  equipamento[id].data.dia = date[0];
  equipamento[id].data.mes = date[1];
  equipamento[id].data.ano = date[2];
}

void insertCpu(int id){

  clearToLineEnd();
  renderColor("Nome da CPU -> ", GREEN);
  readString(equipamento[id].cpu.name, 50);

  //while the user's option is not valid (between 0 and 10,exlusive)ask continously
  clearToLineEnd();
  renderColor("Clocks da CPU -> ", GREEN);
  do {
    readFloat(&equipamento[id].cpu.clock, 20);
    if (equipamento[id].cpu.clock <= 0 || equipamento[id].cpu.clock >= 10) {
      showInvalidOption();
    }
  }while (equipamento[id].cpu.clock <= 0 || equipamento[id].cpu.clock >= 10);
}

void insertDepartament(int id){
  clearToLineEnd();
  renderColor("Departamento -> ", GREEN);
  readString(equipamento[id].departamento, 50);
}

void insertInsurance(int id){
  //insurance start must be a positive number
  clearToLineEnd();
  renderColor("Garantia em Meses -> ", GREEN);
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
  renderColor("Quantidade de RAM (GB) -> ", GREEN);
  do {
    readInt(&equipamento[id].ram, 10);
    if (equipamento[id].ram <= 0 || equipamento[id].ram >= 1000) {
      showInvalidOption();
    }
  }while (equipamento[id].ram <= 0 || equipamento[id].ram >= 1000);
}

void insertOS(int id){
  clearToLineEnd();
  renderColor("Sistema Operativo -> ", GREEN);
  readString(equipamento[id].sistema, 50);
}


/* Disk Insert */
void insertDiskName(int id){
  int diskId = equipamento[id].diskNum;
  clearToLineEnd();
  renderColor("Nome do disco -> ", GREEN);
  readString(equipamento[id].discos[diskId].name, 50);
}

void insertDiskSize(int id){
  int diskId = equipamento[id].diskNum;
  //while the user's option is not valid (between 0 GB and 22 TB)ask continously
  clearToLineEnd();
  renderColor("Tamanho do Disco -> ", GREEN);
  do {
    readInt(&equipamento[id].discos[diskId].capacidade, 20);
    if (equipamento[id].discos[diskId].capacidade <= 0 || equipamento[id].discos[diskId].capacidade >= 22000) {
      showInvalidOption();
    }
  }while (equipamento[id].discos[diskId].capacidade <= 0 || equipamento[id].discos[diskId].capacidade >= 22000);
}

void insertDisk(int id){
  insertDiskName(id);
  insertDiskSize(id);
  equipamento[id].diskNum++;
}


/* Network Board Insert */
int uniqueIp(int ip[4]){
  int strikes = 0;
  for (int equipment = 0;  equipment < maxEquipmentId; equipment++) {
    for (int card = 0; card < equipamento[equipment].networkCardNum; card++) {
      for (int i = 0; i < 4; i++) {
        if (ip[i] == equipamento[equipment].placas[card].ip[i]) {
          strikes++;
          if (strikes == 4) {
            return  False;
          }
        }
      }
    }
  }
  return True;
}

void insertIp(int id){
  int networkCardId = equipamento[id].networkCardNum;
  char tempString[20];
  int ip[4];
  //while the user's input doest not satisfy isValidIp ask continously
  clearToLineEnd();
  renderColor("IP -> ", GREEN);
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

void insertMask(int id){
  int networkCardId = equipamento[id].networkCardNum;
  char tempString[20];
  int mask[4];
  //while the user's input doest not satisfy isValidIp ask continously
  clearToLineEnd();
  renderColor("Mascara -> ", GREEN);
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

void calculateBroadcast(int id){
  int networkCardId = equipamento[id].networkCardNum;
  int ip[4], mask[4];
  for (int i = 0; i < 4; i++) {
    ip[i] = equipamento[id].placas[networkCardId].ip[i];
    mask[i] = equipamento[id].placas[networkCardId].mask[i];
    if (mask[i] == 0) {
      equipamento[id].placas[networkCardId].broadcast[i] = 255;
    }else {
      equipamento[id].placas[networkCardId].broadcast[i] = ip[i];
    }
  }
}

void insertNetworkCard(int id){
  insertIp(id);
  insertMask(id);
  calculateBroadcast(id);
  equipamento[id].networkCardNum++;
}


/* APP insert */
void insertAppVersion(int id){
  int appId = equipamento[id].appNum;
  clearToLineEnd();
  renderColor("Versao da App -> ", GREEN);
  readString(equipamento[id].app[appId].versao, 20);
}

void insertAppExpireDate(int id){
  int appId = equipamento[id].appNum;
  int date[3];
  char tempString[20];

  //while the user's option doest not satisfy isValidDate ask continously
  clearToLineEnd();
  renderColor("Insira a validade (dd/mm/yyyy) -> ", GREEN);
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
  int appNum = equipamento[id].appNum;
  equipamento[id].app[appNum].appId = insertApp();
  insertAppVersion(id);
  insertAppExpireDate(id);
  equipamento[id].appNum++;
}

int insertApp(){
  clearToLineEnd();
  renderColor("Nome da aplicaçao -> ", GREEN);
  readString(app[maxAppId].name, 50);
  clearToLineEnd();
  renderColor("Breve descriçao -> ", GREEN);
  readString(app[maxAppId].descricao, 100);
  maxAppId++;
  return maxAppId-1;
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
  insertDisk(maxEquipmentId);
  insertNetworkCard(maxEquipmentId);
  
  //idk wtf im doing
  // do {
  //   printf("Se a app desejada nao estiver na lista escreva o nome.");
  //   printf("Se numero for 0 termina inserçao");
  //   printf("Escolha uma aplicaçao (numero) ->");
  //   insertInstalledApp(maxEquipmentId);
  // } while(tempInt != 0);
  maxEquipmentId++;
}
