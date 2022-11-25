#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define prefix "\x1b["

/*----- Print Functions --------*/
void linha(int size);
void titulo(char *title);


/*----- Cursor Control ------*/
void moveCursor(int line, int column);
void upCursor(int lines);
void downCursor(int lines);
void rightCursor(int columns);
void leftCursor(int columns);
void saveCursor();
void restoreCursor();

/*----- Clear Functions -----*/
void clear();
void clearToScreenStart();
void clearToScreenEnd();
void clearToLineStart();
void clearToLineEnd();
void cleanLine();


#endif //UI_H
