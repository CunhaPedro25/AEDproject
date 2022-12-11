#include "menu.h"

extern Equipamento equipamento[256];
extern int maxAppId;
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

  printf("\n\n");
  printf(PROMPT);
  do {
    char temporary[10];

    readString(temporary, 10);

    if(strcmp(temporary, "s") == 0 || strcmp(temporary, "S") == 0 ){
      return 0;
    }

    if(!isInt(temporary)){
      showInvalidOption();
      continue;
    }

    char *trash;
    option = strtol(temporary, &trash, 10);

    if(option < 1 || option > size) {
      showInvalidOption();
    }
  } while (option < 1 || option > size);

  return option;
}

void editApps(int id){
  int value;

  do {
    char *options[2] =
        {
            "Nome",
            "Descrição"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Editar Aplicações", options, size, "sub");

    clear();
    switch (value) {
      case 1:
        editAppName(id);
        break;
      case 2:
        editAppDescription(id);
        break;

      default:
        value = 0;
    }
  }while(value != 0);

  clear();
}

void editDisksMenu(int id){
  int value;

  do {
    char *options[3] =
        {
            "Inserir Disco",
            "Editar Discos",
            "Eliminar Disco"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Editar Discos", options, size, "sub");

    clear();
    switch (value) {
      case 1:
        renderTitle("Inserir Disco");
        insertDisk(id);
        break;
      case 2:
        editDisk(id);
        break;
      case 3:
        deleteDisk(id);
        break;

      default:
        value = 0;
    }
  }while(value != 0);

  clear();
}

void editInstalledAppsMenu(int id){
  int value;

  do {
    char *options[3] =
        {
            "Inserir Aplicações",
            "Editar Aplicações",
            "Eliminar Aplicação"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Editar Aplicações", options, size, "sub");

    clear();
    switch (value) {
      case 1:
        renderTitle("Inserir Aplicações");
        if(maxAppId > 0){
          showApps(id);
        }else{
          askNewApp(id);
        }
        break;
      case 2:
        editInstalledApps(id);
        break;
      case 3:
        deleteInstalledApp(id);
        break;

      default:
        value = 0;
    }
  }while(value != 0);

  clear();
}

void editNetworkMenu(int id){
  int value;

  do {
    char *options[3] =
        {
            "Inserir Placa",
            "Editar Placa",
            "Eliminar Placa"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Editar Discos", options, size, "sub");

    clear();
    switch (value) {
      case 1:
        renderTitle("Inserir Placa");
        insertNetworkCard(id);
        break;
      case 2:
        editNetwork(id);
        break;
      case 3:
        deleteNetwork(id);
        break;

      default:
        value = 0;
    }
  }while(value != 0);

  clear();
}

void editEquipment(int id){
  int value;

  do {
    char *options[11] =
        {
            "Tipo",
            "Aquisição",
            "Departamento",
            "Garantia",
            "RAM",
            "Sistema Operativo",
            "CPU Name",
            "CPU Clock",
            "Discos",
            "Aplicações Instaladas",
            "Placas de Rede",
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Editar Equipamento", options, size, "sub");

    clear();
    switch (value) {
      case 1:
        editType(id);
        break;
      case 2:
        editAquisitionDate(id);
        break;
      case 3:
        editDepartament(id);
        break;
      case 4:
        editInsurance(id);
        break;
      case 5:
        editRam(id);
        break;
      case 6:
        editOS(id);
        break;
      case 7:
        editCpuName(id);
        break;
      case 8:
        editCpuClock(id);
        break;
      case 9:
        if(equipamento[id].diskNum > 0) {
          editDisksMenu(id);
        }else{
          renderTitle("Inserir Discos");
          if(askConfirmation("Adicionar Disco")) {
            insertDisk(id);
          }
        }
        break;
      case 10:
        if(equipamento[id].appNum > 0) {
          editInstalledAppsMenu(id);
        }else{
          renderTitle("Inserir Aplicações");
          if(maxAppId > 0){
            showApps(id);
          }else{
            askNewApp(id);
          }
        }
        break;
      case 11:
        if(equipamento[id].networkCardNum > 0) {
          editNetworkMenu(id);
        }else{
          renderTitle("Inserir Place de Rede");
          if(askConfirmation("Adicionar Place de Rede")) {
            insertNetworkCard(id);
          }
        }
        break;

      default:
        value = 0;
    }
  }while(value != 0);

  clear();
}

/**
 *  @brief Menu for aplications with respective options and functions
 *
 *  @options Insert, List, Edit, Delete
 */
void aplicacoesMenu(){
  int value;

  do {
    char *options[3] =
        {
            "Inserir",
            "Lista",
            "Paginas"
        };
    size_t size = sizeof(options)/sizeof(options[0]);

    value = menu("Aplicações", options, size, "sub");

    switch (value) {
      case 1:
        insertNewApp();
        break;
      case 2:
        aplicacoesTable();
        break;
      case 3:
        appPage(0);
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
    char *options[2] =
        {
            "Equipamentos",
            "Aplicações"
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

      default:
        value = 0;
    }
  }while(value != 0);

  clear(); // Clean screen when the program ends
}
