/*
 *  @brief Estrutura de dados para equipamentos
 *
 */
#ifndef STRUCTERS_H

#define STRUCTERS_H

typedef struct{
  char name[50];
  char descricao[100];
}Apps;

typedef struct {
  int ip[4];
  int mask[4];
  int broadcast[4];
} NetworkCards;

typedef struct{
  char name[50];
  int capacidade; // Capacidade do disco
} Disks;

typedef struct{
  int appId;
  char version[20];
  struct License {
    int day;
    int months;
    int year;
  } license;
} InstalledApps;

typedef struct Equipamentos {

  int type;

  struct Insurance {
    int day; // equipment[0].data.day
    int month;
    int year;
  } data;

  char department[50];
  int warranty; // Em meses

  struct CPUs {
    char name[50];
    float clock; // Velociade do relogio
  } cpu;

  int  ram;
  char operatingSystem[50];

  int diskNum;
  int appNum;
  int networkCardNum;
  Disks disk[256];
  NetworkCards networkCard[256];
  InstalledApps app[256];

} Equipment;

#endif // STRUCTERS_H
