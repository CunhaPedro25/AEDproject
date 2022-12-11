#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#include "../ui/utilities/ui.h"
#include "../structures/structers.h"

typedef enum {
  False, True
}boolean;

typedef enum{
  RAM,
  OS,
  APP,
  LICENSE,
  WARRANTY,
  NETWORK
} filter;

/* Time Functions */
const char* currentDate();
const char* currentHours();
boolean checkIfExpired(int day, int month, int year);
int checkIfWarrantyExpired(int day, int month, int year, int warranty);

/* Verification Functions */
int validNumber(char *option, int maxID);
boolean isInt(char *text);
boolean isFloat(char *text);
boolean isValidDate(const char *date);
boolean isValidIp(char *ip);
int countDigits(int number);
boolean isEmpty(char *text);

/* Read functions */
void readString(char *string,int maxInputSize);
void readInt(int *n, int maxInputSize);
void readFloat(float *n, int maxInputSize);
boolean askConfirmation(char *string);

/* String Manipulation or count */
size_t strlen_utf8(const char *string);
int strcut(char *str, int begin, int len);
const char* truncate(char *string, int limit);
void removeNewline(char *string);

/* Delete Functions */
void deleteEquipment(int id);
void deleteDisk(int id);
void deleteInstalledApp(int id);
void deleteNetwork(int id);
void deleteApps(int id);

/* Only Edit Functions */
void editAppName(int id);
void editAppDescription(int id);
void editType(int id);
void editAquisitionDate(int id);
void editDepartament(int id);
void editInsurance(int id);
void editRam(int id);
void editOS(int id);
void editCpuName(int id);
void editCpuClock(int id);
void editDisk(int id);
void editInstalledApps(int id);
void editNetwork(int id);

/* Get total disk space */
int getTotalDiskSpace(int id);

/* Get id From a specific Range */
int getID(int range);

/* Insert and Edit Functions */
boolean insertDate(const char *dateStr, int *date);
void insertType(int id);
void insertAquisitionDate(int id);
void insertCpuName(int id);
void insertCpuClock(int id);
void insertCpu(int id);
void insertOS(int id);
void insertDepartament(int id);
void insertRam(int id);
void insertInsurance(int id);
/*--Disk--*/
void insertDiskName(int id, int diskID);
void insertDiskSize(int id, int diskID);
void insertDisk(int id);
/*--IP--*/
void insertIp(int id, int networkCardId);
void insertMask(int id, int networkCardId);
void calculateBroadcast(int id, int networkCardId);
void insertNetworkCard(int id);
/*--APPS--*/
void insertAppVersion(int id, int appId);
void insertAppExpireDate(int id, int appId);
void insertInstalledApp(int id);
void insertAppName(int id);
void insertAppDescripton(int id);
int insertApp();
void askNewApp(int id);
void showApps(int id);
/*--Main--*/
void insertNewApp();
void insertEquipment();

/* Extra */
void renderInstalledApps(int id);
void renderIP(int ip[4]);

/*----- Print Functions --------*/
void closedLine(int size, int isTop);
void line(int size, int breakLine);
void renderTitle(const char *title);
void showSpecificInvalidOption(char *text);
void showInvalidOption();

#endif //FUNCTIONS_H
