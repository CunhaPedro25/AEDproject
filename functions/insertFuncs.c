#include "functions.h"
#include "../includes.h"

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

void insertEquipment(){
  insertType(maxEquipmentId);
  insertAquisitionDate(maxEquipmentId);
  insertCpu(maxEquipmentId);
  insertOS(maxEquipmentId);
  printf("Tipo->%d\n", equipamento[maxEquipmentId].type);
  printf("Dia->%d\n", equipamento[maxEquipmentId].data.dia);
  printf("Mes->%d\n", equipamento[maxEquipmentId].data.mes);
  printf("Ano->%d\n", equipamento[maxEquipmentId].data.ano);
  printf("Nome CPU->%s\n", equipamento[maxEquipmentId].cpu.name);
  printf("Tipo->%.2f\n", equipamento[maxEquipmentId].cpu.clock);
  printf("OS->%s\n", equipamento[maxEquipmentId].sistema);

  maxEquipmentId++;
}
