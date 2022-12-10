#include "functions.h"

extern Equipamento equipamento[256];
extern int maxEquipmentId;

void deleteEquipment(int id){
  for (int i = id; i < maxEquipmentId; i++) {
    equipamento[i] = equipamento[i+1];
  }
  maxEquipmentId--;
}
