/*
 *  @brief Estrutura de dados para equipamentos
 *
 */
#ifndef equipamentos_h

#define equipamentos_h

typedef struct {
  char *ip;
  char *mask;
  char *broadcast;
} Placas;

typedef struct{
  char *name;
  int capacidade; // Capacidade do disco
} Discos;

typedef struct{
  char versao;
  struct Validade {
    int dia;
    int mes;
    int ano;
  } validade;
} Aplicacoes;

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

  Discos discos[256];
  Placas placas[256];
  Aplicacoes aplicacoes[256];

} Equipamento;

Equipamento equipamento[256];
#endif // !equipamentos_h
