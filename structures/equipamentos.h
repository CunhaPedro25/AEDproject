/*
 *  @brief Estrutura de dados para equipamentos
 *
 */
#ifndef equipamentos_h

#define equipamentos_h

typedef struct Equipamentos {

  struct Aquisicao {
    int dia; // equipamento[0].data.dia
    int mes;
    int ano;
  } data;

  char *departamento;
  int garantia; // Em meses

  struct CPUs {
    char *name;
    float clock; // Velociade do relogio
  } cpu;

  struct Discos {
    char *name;
    int capacidade; // Capacidade do disco
  } disco;

  char *ram;
  char *sistema;

  struct Aplicacoes {
    char versao;
    struct Validade {
      int dia;
      int mes;
      int ano;
    } validade;
  } aplicaoes;

  struct Placas {
    char *ip;
    char *mask;
    char *broadcast;
  } placas;
} Equipamento;

extern Equipamento equipamento[256];
#endif // !equipamentos_h
