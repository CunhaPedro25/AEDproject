#ifndef MANUAL_MD_UI_H
#define MANUAL_MD_UI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define prefix "\x1b["

/*----- Print Functions --------*/
void linha(int size);
void titulo(char *title);


/*----- Cursor Control ------*/
void saveCursor();
void restoreCursor();

/*----- Clear Functions -----*/
void clear();
void clearToEnd();



#endif //MANUAL_MD_UI_H
