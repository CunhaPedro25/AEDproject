#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#include "../ui/utilities/ui.h"
#include "../structures/equipamentos.h"

typedef enum {
  False, True
}boolean;

/* Time Functions */
const char* currentDate();
const char* currentHours();

/* Verification Functions */
int validNumber(char *option, int maxID);
boolean isInt(char *text);
boolean isFloat(char *text);
boolean isValidDate(char *date);
boolean isValidIp(char *ip);
int countDigits(int number);

/* Read functions */
void readString(char *string,int maxInputSize);
void readInt(int *n, int maxInputSize);
void readFloat(float *n, int maxInputSize);

/* String Manipulation or count */
size_t strlen_utf8(const char *string);
int strcut(char *str, int begin, int len);
const char* truncate(char *string, int limit);
void removeNewline(char *string);

/* Delete Functions */
void deleteEquipment(int id);

/* Insert and Edit Functions */
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
void insertNetworkCard(int id);
void insertInstalledApp(int id);
int insertApp();
void insertDisk(int id);
void insertEquipment();
#endif //FUNCTIONS_H
