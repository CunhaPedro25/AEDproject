#include "functions.h"

extern Apps app[256];
extern Equipment equipment[256];
extern int maxAppId;
extern int maxEquipmentId;

void deleteEquipment(int id){
  for (int i = id; i < maxEquipmentId; i++) {
    equipment[i] = equipment[i + 1];
  }
  maxEquipmentId--;
}

void deleteDisk(int id){
  renderTitle("Eliminar Disco");
  printf("Escolha o disco ([s] - sair)\n");
  for (int i = 0; i < equipment[id].diskNum; i++) {
    int capacity = equipment[id].disk[i].capacidade >= 1000 ? equipment[id].disk[i].capacidade / 1000 : equipment[id].disk[i].capacidade;
    printf("%d - %-10s %d %s\n", i+1, equipment[id].disk[i].name, capacity, equipment[id].disk[i].capacidade >= 1000 ? "TB" : "GB");
  }
  int diskID = getID(equipment[id].diskNum);

  if(diskID != 0){
    for (int i = diskID-1; i < equipment[id].diskNum; i++) {
      equipment[id].disk[i] = equipment[id].disk[i + 1];
    }

    equipment[id].diskNum--;
  }
}

void deleteInstalledApp(int id){
  renderTitle("Eliminar Aplicação");
  printf("Escolha uma Aplicação ([s] - sair)\n");
  renderInstalledApps(id);
  int appID = getID(equipment[id].appNum);

  if(appID != 0){
    for (int i = appID-1; i < equipment[id].appNum; i++) {
      equipment[id].app[i] = equipment[id].app[i + 1];
    }

    equipment[id].appNum--;
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
  for (int i = 0; i < equipment[id].networkCardNum; i++) {
    printf("%d - ", i+1);
    renderIP(equipment[id].networkCard[i].ip);
    printf(" ");
    renderIP(equipment[id].networkCard[i].mask);
    printf("\n");
  }
  int networkID = getID(equipment[id].networkCardNum);

  if(networkID != 0){
    for (int i = networkID; i < equipment[id].networkCardNum; i++) {
      equipment[id].networkCard[i] = equipment[id].networkCard[i + 1];
    }

    equipment[id].networkCardNum--;
  }
}


void deleteApps(int id){
  for (int i = id; i < maxAppId; i++) {
    app[i] = app[i+1];
  }
  maxAppId--;

  for (int i = 0; i < maxEquipmentId; i++) {
    int startDeleting = False;
    for (int appID = 0; appID < equipment[i].appNum; appID++){
      if(equipment[i].app[appID].appId == id && startDeleting == False) startDeleting = True;

      if(startDeleting == True) {
        equipment[i].app[appID] = equipment[i].app[appID + 1];
        equipment[i].app[appID].appId--;
      }
    }
    if(startDeleting == True){ equipment[i].appNum--;}
  }
}
