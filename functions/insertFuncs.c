#include "functions.h"
#include <stdio.h>

extern int maxEquipmentId;
extern Equipamento equipamento[256];
extern Apps app[256];
extern int maxAppId;

//Devides an already valide date into 3 ints
void insertDate(char *dateStr, int *date){
  sscanf(dateStr, "%d/%d/%d", &date[0],&date[1],&date[2]); 
}
 
void insertType(int id){
  char temp[20];
  int tempInt;

  //while the user's option is not valid (1 or 2)ask continously
  do {
  printf("Insira o tipo de dispositivo 1 para computador 2 para servidor\n");
  printf("Tipo de dispositivo ->");
  readInt(&equipamento[id].type, 20);
  } while(equipamento[id].ram !=1 || equipamento[id].ram != 2);
}

void insertAquisitionDate(int id){
  int date[3];
  char tempString[20];

  //while the user's option doest not satisfy isValidDate ask continously
  do {
  printf("Insira a validade (dd/mm/yyyy) ->");
  readString(tempString, 20);
  insertDate(tempString, date);
  equipamento[id].data.dia = date[0];
  equipamento[id].data.mes = date[1];
  equipamento[id].data.ano = date[2];
  } while(isValidDate(tempString) == False);
}

void insertCpu(int id){

  printf("Nome da CPU ->");
  readString(equipamento[id].cpu.name, 50);

  //while the user's option is not valid (between 0 and 10,exlusive)ask continously
  do {
  printf("Clocks da CPU ->");
  readFloat(&equipamento[id].cpu.clock, 20);
  }while (equipamento[id].cpu.clock <= 0 || equipamento[id].cpu.clock >= 10);
}

void insertOS(int id){
  printf("Sistema Operativo ->");
  readString(equipamento[id].sistema, 50);
}

void insertDepartament(int id){
  printf("Departamento ->");
  readString(equipamento[id].departamento, 50);
}

void insertRam(int id){
  //while the user's option is not valid (between 0 and 1000 exlusive)ask continously
  do {
  printf("Quantidade de RAM (GB) ->");
  readInt(&equipamento[id].ram, 10);
  }while (equipamento[id].ram <= 0 || equipamento[id].ram >= 1000);
}

void insertDiskName(int id){
  int diskId = equipamento[id].diskNum;
  printf("Nome do disco ->");
  readString(equipamento[id].discos[diskId].name, 50);
}

void insertDiskSize(int id){
  int diskId = equipamento[id].diskNum;
  //while the user's option is not valid (between 0 GB and 22 TB)ask continously
  do {
  printf("Tamanho do Disco ->");
  readInt(&equipamento[id].discos[diskId].capacidade, 20);
  }while (equipamento[id].discos[diskId].capacidade <= 0 || equipamento[id].discos[diskId].capacidade >= 22000);
}

void insertAppVersion(int id){
  int appId = equipamento[id].appNum;
  printf("Versao da App ->");
  readString(equipamento[id].app[appId].versao, 20);
}

void insertAppExpireDate(int id){
  int appId = equipamento[id].appNum;
  int date[3];
  char tempString[20];

  //while the user's option doest not satisfy isValidDate ask continously
  do {
  printf("Insira a validade (dd/mm/yyyy) ->");
  readString(tempString, 20);
  insertDate(tempString, date);
  equipamento[id].app[appId].validade.dia = date[0];
  equipamento[id].app[appId].validade.mes = date[1];
  equipamento[id].app[appId].validade.ano = date[2];
  } while(isValidDate(tempString) == False);
}

void insertInsurance(int id){
  //insurance start must be a positive number
  do {
  printf("Garantia do produto(meses) ->");
  readInt(&equipamento[id].garantia, 20);
  }while (equipamento[id].garantia < 0);
}

void insertIp(int id){
  int networkCardId = equipamento[id].networkCardNum;
  char tempString[20];
  int ip[4];
  //while the user's input doest not satisfy isValidIp ask continously
  do {
  printf("Ip ->");
  readString(tempString, 20);
  } while(isValidIp(tempString) == False);
  // assign the ip values to the struct of id
  for (int i = 0; i < 4; i++) {
    ip[i] = equipamento[id].placas[networkCardId].ip[i];
  }
  sscanf(tempString,"%d.%d.%d.%d", &ip[0],&ip[1],&ip[2],&ip[3]);
}

void insertMask(int id){
  int networkCardId = equipamento[id].networkCardNum;
  char tempString[20];
  int mask[4];
  //while the user's input doest not satisfy isValidIp ask continously
  do {
  printf("Mascara ->");
  readString(tempString, 20);
  } while(isValidIp(tempString) == False);
  // assign the mask values to the struct of id
  for (int i = 0; i < 4; i++) {
    mask[i] = equipamento[id].placas[networkCardId].mask[i];
  }
  sscanf(tempString,"%d.%d.%d.%d", &mask[0],&mask[1],&mask[2],&mask[3]);
}

void insertNetworkCard(int id){
  insertIp(id);
  insertMask(id);
  equipamento[id].networkCardNum++;
}

void insertInstalledApp(int id){
  int appNum = equipamento[id].appNum;
  equipamento[id].app[appNum].appId = insertApp();
  insertAppVersion(id);
  insertAppExpireDate(id);
  equipamento[id].appNum++;
}

void insertDisk(int id){
  insertDiskName(id);
  insertDiskSize(id);
  equipamento[id].diskNum++;
}

int insertApp(){
  printf("Nome da aplicaçao ->");
  readString(app[maxAppId].name, 50);
  printf("Breve descriçao ->");
  readString(app[maxAppId].descricao, 100);
  maxAppId++;
  return maxAppId-1;
}

void insertEquipment(){
  int tempInt = -1;
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
  do {
    printf("Se a app desejada nao estiver na lista escreva o nome.");
    printf("Se numero for 0 termina inserçao");
    printf("Escolha uma aplicaçao (numero) ->");
    insertInstalledApp(maxEquipmentId);
  } while(tempInt != 0);
  maxEquipmentId++;
}
