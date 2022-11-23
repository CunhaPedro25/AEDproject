#include "main.h"

int menu(char *title, char *options[256]);

void clearMenu(){
  system("cls");
}

void aplicacoes(){
  int value;

  do {
    char *options[5] =
        {
            "Inserir",
            "Listar",
            "Editar",
            "Eliminar",
            NULL
        };
    value = menu("Aplicações", options);

    switch (value) {
      case 1:
      case 2:
      case 3:
      case 4:
        clearMenu();
        break;

      default:
        value = 0;
    }
  } while (value != 0);
}

void equipamentos(){
  int value;

  do {
    char *options[5] =
        {
            "Inserir",
            "Listar",
            "Editar",
            "Eliminar",
            NULL
        };
    value = menu("Equipamentos", options);

    switch (value) {
      case 1:
      case 2:
      case 3:
      case 4:
        aplicacoes();
        break;

      default:
        value = 0;
    }
  } while (value != 0);
}

void mainMenu(){
  int value;

  do {
    char *options[4] =
        {
            "Equipamentos",
            "Aplicações",
            "Placas de rede",
            NULL
        };
    value = menu("Gestão de Equipamentos", options);

    switch (value) {
      case 1:
        equipamentos();
        break;
      case 2:
      case 3:
        aplicacoes();
        break;

      default:
        value = 0;
    }
  }while(value != 0);
}

int menu(char *title, char *options[256]){
  int option;
  int size = 0;
  while(options[size] != NULL){
    size++;
  }

  do {
    clearMenu();
    printf("/*-- %s --*/\n", title);

    for (int i = 0; i < size; ++i) {
      printf("%d - %s\n", i+1, options[i]);
    }
    printf("0 - Sair");

    printf("\n\nOpção: ");
    scanf("%d", &option);
    fflush(stdin);
  } while (option < 0 || option > size);

  for (int i = 0; i < size; ++i) {
    options[i] = NULL;    // Clean Options
  }

  return option;
}