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

  printf("Clocks da CPU ->");
  readFloat(&equipamento[id].cpu.clock, 20);
}

void insertOS(int id){
  printf("Sistema Operativo ->");
  readString(equipamento[id].sistema, 50);
}

void insertDepartamento(int id){
  printf("Departamento ->");
  readString(equipamento[id].departamento, 50);
}

void insertRam(int id){
  printf("Quantidade de RAM (GB) ->");
  readInt(&equipamento[id].ram, 10);
}

void insertDiskName(int id){
  int diskId = equipamento[id].diskNum;
  printf("Nome do disco ->");
  readString(equipamento[id].discos[diskId].name, 50);
}

void insertDiskSize(int id){
  int diskId = equipamento[id].diskNum;
  printf("Tamanho do Disco ->");
  readInt(&equipamento[id].discos[diskId].capacidade, 20);
}

void insertAppVersion(int id){
  int appId = equipamento[id].appNum;
  printf("Versao da App ->");
  readString(equipamento[id].app[appId].versao, 20);
}

void insertAppExpireDate(int id){
  int appId = equipamento[id].appNum;

  printf("Dia ->");
  readInt(&equipamento[id].app[appId].validade.dia, 20);

  printf("Mes ->");
  readInt(&equipamento[id].app[appId].validade.mes, 20);

  printf("Ano ->");
  readInt(&equipamento[id].app[appId].validade.ano, 20);
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

void insertEquipment(){
  insertType(maxEquipmentId);
  insertAquisitionDate(maxEquipmentId);
  insertCpu(maxEquipmentId);
  insertOS(maxEquipmentId);

  maxEquipmentId++;
}
