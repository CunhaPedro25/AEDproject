#ifndef CHARS_H
#define CHARS_H

#ifdef WIN32
  #define LINE "-"
  #define GROUP_LINES "-----"
  #define VLINE "|"
  #define TOP_LEFT_LINE "-"
  #define TOP_RIGHT_LINE "-"
  #define BOTTOM_LEFT_LINE "-"
  #define BOTTOM_RIGHT_LINE "-"
  #define LEFT_ARROW "<-"
  #define RIGHT_ARROW "->"
  #define PROMPT "> "
  #define TITLE_LEFT "/*-- "
  #define TITLE_RIGHT " --*/"
#else
  #define LINE "─"
  #define GROUP_LINES "─────"
  #define VLINE "│"
  #define TOP_LEFT_LINE "┌"
  #define TOP_RIGHT_LINE "┐"
  #define BOTTOM_LEFT_LINE "└"
  #define BOTTOM_RIGHT_LINE "┘"
  #define LEFT_ARROW "❮─"
  #define RIGHT_ARROW "─❯"
  #define PROMPT "❯ "
  #define TITLE_LEFT "│    "
  #define TITLE_RIGHT "    │"
#endif

#endif //CHARS_H
