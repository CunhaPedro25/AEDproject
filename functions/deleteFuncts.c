#include "functions.h"

extern Apps app[256];
extern Equipamento equipamento[256];
extern int maxAppId;
extern int maxEquipmentId;

void deleteEquipment(int id){
  for (int i = id; i < maxEquipmentId; i++) {
    equipamento[i] = equipamento[i+1];
  }
  maxEquipmentId--;
}

void deleteDisk(int id){
  renderTitle("Eliminar Disco");
  printf("Escolha o disco ([s] - sair)\n");
  for (int i = 0; i < equipamento[id].diskNum; i++) {
    int capacity = equipamento[id].discos[i].capacidade >= 1000 ? equipamento[id].discos[i].capacidade/1000 : equipamento[id].discos[i].capacidade;
    printf("%d - %-10s %d %s\n", i+1, equipamento[id].discos[i].name, capacity, equipamento[id].discos[i].capacidade >= 1000 ? "TB" : "GB");
  }
  int diskID = getID(equipamento[id].diskNum);

  if(diskID != 0){
    for (int i = diskID; i < equipamento[id].diskNum; i++) {
      equipamento[id].discos[i] = equipamento[id].discos[i+1];
    }

    equipamento[id].diskNum--;
  }
}

void deleteInstalledApp(int id){
  renderTitle("Eliminar Aplicação");
  printf("Escolha uma Aplicação ([s] - sair)\n");
  renderInstalledApps(id);
  int appID = getID(equipamento[id].appNum);

  if(appID != 0){
    for (int i = appID; i < equipamento[id].appNum; i++) {
      equipamento[id].app[i] = equipamento[id].app[i+1];
    }

    equipamento[id].appNum--;
  }
}

void renderIP(int ip[4]){
  for (int i = 0; i < 4; i++) {
    printf("%d", ip[i]);
    if(i != 3){
      printf(".");
    }
  }
}

void deleteNetwork(int id){
  renderTitle("Eliminar Placa de Rede");
  printf("Escolha a Placa ([s] - sair)\n");
  for (int i = 0; i < equipamento[id].networkCardNum; i++) {
    printf("%d - ", i+1);
    renderIP(equipamento[id].placas[i].ip);
    printf(" ");
    renderIP(equipamento[id].placas[i].mask);
    printf("\n");
  }
  int networkID = getID(equipamento[id].networkCardNum);

  if(networkID != 0){
    for (int i = networkID; i < equipamento[id].networkCardNum; i++) {
      equipamento[id].placas[i] = equipamento[id].placas[i+1];
    }

    equipamento[id].networkCardNum--;
  }
}


void deleteApps(int id){
  for (int i = id; i < maxAppId; i++) {
    app[i] = app[i+1];
  }
  maxAppId--;

  for (int i = 0; i < maxEquipmentId; i++) {
    int startDeleting = False;
    for (int appID = 0; appID < equipamento[i].appNum; appID++){
      if(equipamento[i].app[appID].appId == id && startDeleting == False) startDeleting = True;

      if(startDeleting == True) {
        equipamento[i].app[appID] = equipamento[i].app[appID + 1];
        equipamento[i].app[appID].appId--;
      }
    }
    if(startDeleting == True){ equipamento[i].appNum--;}
  }
}
