#include "menu.h"

/**
 *
 *  @brief Creates Menu with custom options and title
 *
 *  @param title {char *} - Menu title
 *  @param options {char **} - Array of stings with options that are used
 *  @param size {int} - Number of elements in the array
 *
 *  @returns {int} - Option selected
 */
int menu(char *title, char **options, size_t size){
  int option;

  do {
    clear();
    titulo(title);

    for (int i = 0; i < size; ++i) {
      printf("%d - %s\n", i+1, options[i]);
    }
    printf("0 - Sair");

    printf("\n\nOpção: ");
    char temporary;
    fflush(stdin);
    scanf("%c", &temporary);
    printf("\n");

    option = temporary - '0';             // Passar 'char' to 'int' mantendo o valor ex: '1' = 1
  } while (option < 0 || option > size);

  return option;
}

void aplicacoes(){
  int value;

  do {
    char *options[4] =
        {
            "Inserir",
            "Listar",
            "Editar",
            "Eliminar"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Aplicações", options, size);

    switch (value) {
      case 1:
      case 2:
      case 3:
      case 4:
        clear();
        break;

      default:
        value = 0;
    }
  } while (value != 0);
}

void equipamentos(){
  int value;

  do {
    char *options[4] =
        {
            "Inserir",
            "Listar",
            "Editar",
            "Eliminar"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Equipamentos", options, size);

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
    char *options[3] =
        {
            "Equipamentos",
            "Aplicações",
            "Placas de rede"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Gest?o de Equipamentos", options, size);

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