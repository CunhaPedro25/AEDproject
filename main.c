#include "includes.h"


Equipamento equipamento[256];
Apps app[256];
int maxEquipmentId = 15;
int maxAppId = 0;

int main(){
  setlocale(LC_ALL, "Portuguese");

  mainMenu();

  clear();
  resetStyles();
  cursorVisibility(1);
  return 0;
}
