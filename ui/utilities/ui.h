#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "chars.h"

#define prefix "\e["

/*----- Cursor Control ------*/
void goHomeCursor();
void lineStartCursor();
void moveCursor(int line, int column);
void upCursor(int lines);
void downCursor(int lines);
void rightCursor(int columns);
void leftCursor(int columns);
void saveCursor();
void restoreCursor();
void cursorVisibility(int state);

/*----- Clear Functions -----*/
void clear();
void clearToScreenStart();
void clearToScreenEnd();
void clearToLineStart();
void clearToLineEnd();
void cleanLine();

/*------ Color Functions ------*/
void textColor(int color);
void backgroundColor(int color);
void resetStyles();
void renderColor(char *string, int color);

#endif //UI_H
