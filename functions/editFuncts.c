#include "functions.h"

extern int maxEquipmentId;
extern Equipment equipment[256];
extern Apps app[256];
extern int maxAppId;

void editAppName(int id){
  renderTitle("Editar Nome");
  insertAppName(id);
}

void editAppDescription(int id){
  renderTitle("Editar Descrição");
  insertAppDescripton(id);
}


void editType(int id){
  renderTitle("Editar Tipo");
  insertType(id);
}

void editAquisitionDate(int id){
  renderTitle("Editar Data de Aquisição");
  insertAquisitionDate(id);
}

void editDepartament(int id){
  renderTitle("Editar Departamento");
  insertDepartament(id);
}

void editInsurance(int id){
  renderTitle("Editar Garantia");
  insertInsurance(id);
}

void editRam(int id){
  renderTitle("Editar RAM");
  insertRam(id);
}

void editOS(int id){
  renderTitle("Editar Sistema Operativo");
  insertOS(id);
}

void editCpuName(int id){
  renderTitle("Editar Nome do CPU");
  insertCpuName(id);
}

void editCpuClock(int id){
  renderTitle("Editar CPU Clock");
  insertCpuClock(id);
}

int getTotalDiskSpace(int id){
  int totalCapacity = 0;
  for (int i = 0; i < equipment[id].diskNum; i++){
    totalCapacity += equipment[id].disk[i].capacidade;
  }

  return totalCapacity;
}

int getID(int range){
  int result;
  printf("\n"PROMPT);
  char option[10];
  char *trash;
  do{
    do{
      readString(option, 10);
      if(strcmp(option, "s") == 0 || strcmp(option, "S") == 0){
        strcpy(option, "0");
      }

      if(isInt(option) == False){
        showInvalidOption();
      }
    } while (isInt(option) == False);

    if(strcmp(option, "s") == 0 || strcmp(option, "S") == 0){
      result = 0;
    }else{
      result = strtol(option, &trash, 10);
    }

    if(result < 1 || result > range){
      showSpecificInvalidOption("[Fora da Range]");
    }
  } while(result < 0 || result > range);

  return result;
}

void editDisk(int id){
  renderTitle("Editar Disco");
  printf("Escolha o disco ([s] - sair)\n");
  for (int i = 0; i < equipment[id].diskNum; i++) {
    int capacity = equipment[id].disk[i].capacidade >= 1000 ? equipment[id].disk[i].capacidade / 1000 : equipment[id].disk[i].capacidade;
    printf("%d - %-10s %d %s\n", i+1, equipment[id].disk[i].name, capacity, equipment[id].disk[i].capacidade >= 1000 ? "TB" : "GB");
  }
  int diskID = getID(equipment[id].diskNum);

  if(diskID != 0){
    moveCursor(5,0);
    clearToScreenEnd();
    renderColor("Disco:\n", GREEN);
    insertDiskName(id, diskID-1);
    insertDiskSize(id, diskID-1);
  }
}

void editInstalledApps(int id){
  renderTitle("Aplicações Instaladas");
  printf("Escolha uma Aplicação ([s] - sair)\n");
  renderInstalledApps(id);
  int appID = getID(equipment[id].appNum);

  if(appID != 0){
    moveCursor(5,0);
    clearToScreenEnd();
    insertAppVersion(id, appID-1);
    insertAppExpireDate(id, appID-1);
  }
}

void editNetwork(int id){
  renderTitle("Placas de Rede");
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
    moveCursor(5,0);
    clearToScreenEnd();
    renderColor("Disco:\n", GREEN);
    insertIp(id, networkID-1);
    insertMask(id, networkID-1);
    calculateBroadcast(id, networkID-1);
  }
}