#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../ui/utilities/ui.h"
#include "../structures/equipamentos.h"

typedef enum {
  False, True
}boolean;

int validNumber(char *option, int maxID);
int isInt(char *text);
int isfloat(char *text);
int strcut(char *str, int begin, int len);
const char* truncate(char *string, int limit);
void removeNewline(char *string);
void readString(char *string,int maxInputSize);
void readInt(int *n, int maxInputSize);
void readFloat(float *n, int maxInputSize);
void insertType(int id);
void insertAquisitionDate(int id);
void insertCpu(int id);
void insertOS(int id);
void insertDepartament(int id);
void insertRam(int id);
void insertDiskName(int id);
void insertDiskSize(int id);
void insertAppVersion(int id);
void insertAppExpireDate(int id);
void insertInsurance(int id);
void insertIp(int id);
void insertMask(int id);
void insertBroadcast(int id);
void insertNetworkCard(int id);
void insertApp(int id);
void insertDisk(int id);
void insertEquipment(int id);
#endif //FUNCTIONS_H
