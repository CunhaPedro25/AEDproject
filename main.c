/*
 *
 *  IPVC - ESTG
 *
 *  Programa criado por:
 *    - Pedro Cunha 30563
 *    - Miguel Alves 29317
 *
 *  Curso Engenharia de Informatica
 *  Realizado para AED - Algoritmo e Estrutura de Dados
 *
 */

#include "includes.h"

Equipment equipment[256];
Apps app[256];
int maxEquipmentId = 0;
int maxAppId = 0;

int main(){
  setlocale(LC_ALL, "Portuguese");

  mainMenu();

  clear();
  resetStyles();
  cursorVisibility(1);
  return 0;
}
