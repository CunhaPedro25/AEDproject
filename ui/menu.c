#include "menu.h"

int isnumber(char *text){
  for(int i = 0; i < strlen(text); i++){
    if(i == 0 && text[i] == '\n'){
      return 0;
    }
    if(!isdigit(text[i]) && text[i] != '\n'){
      return 0;
    }
  }
  return 1;
}

void invalidOption(){
  textColor(RED);
  printf("[Opção Invalida]");    // Show error message
  resetStyles();
  restoreCursor();
  clearToLineEnd();
}

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
int menu(char *title, char **options, size_t size){
  int option;

  clear();
  titulo(title);

  for (int i = 0; i < size; ++i) {
    printf("%d - %s\n", i+1, options[i]);
  }
  printf("0 - Sair");

  printf("\n\nOpção: ");
  do {
    saveCursor();
    char temporary[10];

    fgets(temporary, 10, stdin);
    fflush(stdin);

    if(!isnumber(temporary)){
      invalidOption();
      continue;
    }

    char *trash;
    option = strtol(temporary, &trash, 10);

    if(option < 0 || option > size) {
      invalidOption();
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

    value = menu("Placas", options, size);

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

/**
 *  @brief Menu for equipment with respective options and functions
 *
 *  @options Insert, List
 */
void equipamentosMenu(){
  int value;

  do {
    char *options[2] =
        {
            "Inserir",
            "Lista"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Equipamentos", options, size);

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

    value = menu("Gestão de Equipamentos", options, size);

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