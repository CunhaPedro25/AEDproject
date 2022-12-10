#include "ui.h"

/*
 *  ALmost all this functions use ANSI Escape Sequences
 *  It's a set of numbers and/or letters that control
 *  the terminal cursor, colors, or can even delete lines
 *
 *  Source: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 *
 */

/*--------------------------*
 * Cursor Control Functions *
 *--------------------------*/

/* Sends cursor back to position 0,0 - top left */
void goHomeCursor() { printf(prefix "H"); }

/* Sends cursor to the start of a line */
void lineStartCursor() { printf(prefix "0G"); }

/**
 * @brief Move cursor to a specific line and column
 *
 *
 * @param line {int} - specific line (starting on 0)
 * @param column {int} - specific column (starting on 0)
 */
void moveCursor(int line, int column) { printf(prefix "%d;%dH", line, column); }

/**
 * @brief Sends cursor *UP* a number of lines
 *
 * @param lines {int} - number of lines to go up
 */
void upCursor(int lines) { printf(prefix "%dA", lines); }

/**
 * @brief Sends cursor *DOWN* a number of lines
 *
 * @param lines {int} - number of lines to go down
 */
void downCursor(int lines) { printf(prefix "%dB", lines); }

/**
 * @brief Sends cursor *RIGHT* a number of columns
 *
 * @param columns {int} - number of columns to go right
 */
void rightCursor(int columns) { printf(prefix "%dC", columns); }

/**
 * @brief Sends cursor *LEFT* a number of columns
 *
 * @param columns {int} - number of columns to go left
 */
void leftCursor(int columns) { printf(prefix "%dD", columns); }

/* Saves the current cursor postion */
void saveCursor() { printf(prefix "s"); }

/* Go ot the last cursor saved position */
void restoreCursor() { printf(prefix "u"); }

void cursorVisibility(int state){
  if(state){
    printf(prefix "?25h");
  }else{
    printf(prefix "?25l");
  }
}


/*------------------------*
 * Clean Screen Functions *
 *------------------------*/

/* Clear entire Screen */

void clear() {
  goHomeCursor();

  #ifdef _WIN32
    system("cls");
  #elif linux
    system("clear");
  #elif __APPLE__
    system("/usr/bin/osascript -e");
  #endif
}

/* Clear from cursor to START of Screen */
void clearToScreenStart() { printf(prefix "1J"); }

/* Clear from cursor to END of Screen */
void clearToScreenEnd() { printf(prefix "0J"); }

/* Clear from cursor to START of Line */
void clearToLineStart() { printf(prefix "1K"); }

/* Clear from cursor to END of Line */
void clearToLineEnd() { printf(prefix "0K"); }

/* Erase entire Line */
void cleanLine() { printf(prefix "2K"); }



/*------------------*
 * Colors Functions *
 *------------------*/
void textColor(int color){
  printf(prefix "%dm", 30+color);
}
void backgroundColor(int color){
  printf(prefix "%dm", 40+color);
}
void resetStyles(){ printf(prefix "0m");}

/*-----------------*
 * Print Functions *
 *-----------------*/

/**
 * @brief Print a line of "-" with a custom size
 *
 * @param size {int} - number of "-" to print (size of line)
 * @param breakLine {bool} - Confirm to add breakLine in the end
 */
void line(int size, int breakLine) {
  for (int i = 0; i < size; ++i) {
    printf("-");
  }
  if(breakLine)
    printf("\n");
}
/**
 *  @brief Print a custom title in the middle of responsive lines
 *
 * @param title {char *} - custom title
 */
void renderTitle(const char *title) {
  int titleSize = (int)(strlen(title) + strlen("/*--  --*/"));
  printf("--%s-", currentDate());
  line(titleSize-21, 0);
  printf("-%s--\n", currentHours());
  printf("/*-- %s --*/\n", title);
  line(titleSize, 1);
}

void showInvalidOption(){
  textColor(RED);
  printf("[Opção Invalida]");    // Show error message
  resetStyles();
  restoreCursor();
  clearToLineEnd();
}