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
  char name[50];
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

  int type;

  struct Aquisicao {
    int dia; // equipamento[0].data.dia
    int mes;
    int ano;
  } data;

  char *departamento;
  int garantia; // Em meses

  struct CPUs {
    char name[50];
    float clock; // Velociade do relogio
  } cpu;

  int ram;
  char *sistema;

  int numeroDiscos;
  Discos discos[256];
  Placas placas[256];
  Aplicacoes aplicacoes[256];

} Equipamento;

#endif // !equipamentos_h
