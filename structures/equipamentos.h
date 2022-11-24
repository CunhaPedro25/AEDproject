/*
 *  @brief Estrutura de dados para equipamentos
 *
 */
#ifndef equipamentos_h

#define equipamentos_h

typedef struct Placas {
  char *ip;
  char *mask;
  char *broadcast;
} Placa;
extern Placa placas[256];

typedef struct Discos {
  char *name;
  int capacidade; // Capacidade do disco
} Disco;
extern Disco discos[256];

typedef struct Aplicacoes {
  char versao;
  struct Validade {
    int dia;
    int mes;
    int ano;
  } validade;
} Aplicacao;
extern Aplicacao aplicacoes[256];

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

  char *ram;
  char *sistema;

  Disco *discos;
  Placa *placas;
  Aplicacao *aplicacoes;

} Equipamento;

extern Equipamento equipamento[256];
#endif // !equipamentos_h
