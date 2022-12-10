#include "functions.h"
#include <stdio.h>

extern int maxEquipmentId;
extern Equipamento equipamento[256];
 
void insertType(int id){
  char temp[20];
  int tempInt;

  printf("Insira o tipo de dispositivo 1 para computador 2 para servidor\n");
  printf("Tipo de dispositivo ->");
  readInt(&equipamento[id].type, 20);
}

void insertAquisitionDate(int id){

  printf("Dia ->");
  readInt(&equipamento[id].data.dia, 20);

  printf("Mes ->");
  readInt(&equipamento[id].data.mes, 20);

  printf("Ano ->");
  readInt(&equipamento[id].data.ano, 20);
}

void insertCpu(int id){

  printf("Nome da CPU ->");
  readString(equipamento[id].cpu.name, 50);

  do {
  printf("Clocks da CPU ->");
  readFloat(&equipamento[id].cpu.clock, 20);
  }while (equipamento[id].cpu.clock <= 0 || equipamento[id].ram >= 10);
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
  char tempString[20];

  printf("Insira a validade (dd/mm/yyyy) ->");
  readString(tempString, 20);
  // printf("Dia ->");
  // readInt(&equipamento[id].app[appId].validade.dia, 20);

  // printf("Mes ->");
  // readInt(&equipamento[id].app[appId].validade.mes, 20);

  // printf("Ano ->");
  // readInt(&equipamento[id].app[appId].validade.ano, 20);
}

void insertInsurance(int id){
  do {
  printf("Garantia do produto(meses) ->");
  readInt(&equipamento[id].garantia, 20);
  }while (equipamento[id].garantia <= 0);
}

void insertIp(int id){
  int networkCardId = equipamento[id].networkCardNum;
  char tempString[20];
  int ip[4];
  do {
  printf("Ip ->");
  readString(tempString, 20);
  } while(isValidIp(tempString) == False);
  for (int i = 0; i < 4; i++) {
    ip[i] = equipamento[id].placas[networkCardId].ip[i];
  }
  sscanf(tempString,"%d.%d.%d.%d", &ip[0],&ip[1],&ip[2],&ip[3]);
}

void insertMask(int id){
  int networkCardId = equipamento[id].networkCardNum;
  char tempString[20];
  int mask[4];
  do {
  printf("Mascara ->");
  readString(tempString, 20);
  } while(isValidIp(tempString) == False);
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

void insertApp(int id){
  insertAppVersion(id);
  insertAppExpireDate(id);
  equipamento[id].appNum++;
}

void insertDisk(int id){
  insertDiskName(id);
  insertDiskSize(id);
  equipamento[id].diskNum++;
}

void insertEquipment(int id){
  insertType(maxEquipmentId);
  insertAquisitionDate(maxEquipmentId);
  insertDepartament(maxEquipmentId);
  insertInsurance(maxEquipmentId);
  insertCpu(maxEquipmentId);
  insertRam(maxEquipmentId);
  insertOS(maxEquipmentId);
  insertDisk(maxEquipmentId);
  insertNetworkCard(maxEquipmentId);
  insertApp(maxEquipmentId);
  maxEquipmentId++;
}
