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
    printf("%d", equipamento[i].appNum );
    if(startDeleting == True){ equipamento[i].appNum -= 1;}
    printf("%d", equipamento[i].appNum );
  }

  system("pause");
}
