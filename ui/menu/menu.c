#include "menu.h"

/**
 *
 *  @brief Creates Menu with custom options and title
 *
 *
 *  @param title {char *} - Menu title
 *  @param options {char **} - Array of stings with options that are used
 *  @param size {int} - Number of elements in the array
 *
 *  @returns {int} - Option selected
 */
int menu(char *title, char **options, size_t size, char *type){
  int option = -1;

  clear();
  renderTitle(title);

  for (int i = 0; i < size; ++i) {
    printf("    [%d] %s\n", i+1, options[i]);
  }
  printf("    [s] %s", strcmp(type, "main") ? "Voltar" : "Sair");

  printf("\n\nOpção: ");
  do {
    saveCursor();
    char temporary[10];

    readString(temporary, 10);

    if((temporary[0] == 's' || temporary[0] == 'S')){
      return 0;
    }

    if(!isInt(temporary)){
      showInvalidOption();
      continue;
    }

    char *trash;
    option = strtol(temporary, &trash, 10);

    if(option < 0 || option > size) {
      showInvalidOption();
    }
  } while (option < 0 || option > size);

  return option;
}

/**
 *  @brief Menu for network boards with respective options and functions
 *
 *  @options List, Edit, Delete
 */
void placasMenu(){
  int value;

  do {
    char *options[3] =
        {
            "Lista",
            "Editar",
            "Eliminar"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Placas", options, size, "sub");

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

/**
 *  @brief Menu for aplications with respective options and functions
 *
 *  @options Insert, List, Edit, Delete
 */
void aplicacoesMenu(){
  int value;

  do {
    char *options[4] =
        {
            "Inserir",
            "Lista",
            "Editar",
            "Eliminar"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Aplicações", options, size, "sub");

    switch (value) {
      case 1:
        clear();
      case 2:
        aplicacoesTable();
        break;
      case 3:
      case 4:
        clear();
        break;

      default:
        value = 0;
    }
  } while (value != 0);
}

/**
 *  @brief Menu for equipment with respective options and functions
 *
 *  @options Insert, List
 */
void equipamentosMenu(){
  int value;

  do {
    char *options[3] =
        {
            "Inserir",
            "Lista",
            "Paginas"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Equipamentos", options, size, "sub");

    switch (value) {
      case 1:
        insertEquipment();
        break;
      case 2:
        equipamentosTable();
        break;
      case 3:
        equipamentPage(0);
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

    value = menu("Gestão de Equipamentos", options, size, "main");

    switch (value) {
      case 1:
        equipamentosMenu();
        break;
      case 2:
        aplicacoesMenu();
        break;
      case 3:
        placasMenu();
        break;

      default:
        value = 0;
    }
  }while(value != 0);

  clear(); // Clean screen when the program ends
}
