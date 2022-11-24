#include "ui.h"

void linha(int size){
  for (int i = 0; i < size; ++i) {
    printf("-");
  }
  printf("\n");
}

void titulo(char *title){
  int larguraTitulo = (int)(strlen(title) + strlen("/*--  --*/"));
  linha(larguraTitulo);
  printf("/*-- %s --*/\n", title);
  linha(larguraTitulo);
}



void saveCursor(){
  printf(prefix "s");
}

void restoreCursor(){
  printf(prefix "u");
}

void clear(){
  system("cls");
}

void clearToEnd(){
  printf(prefix "0J");
}