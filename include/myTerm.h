#pragma once
#ifndef MYTERM_H
#define MYTERM_H

#include <unistd.h> // Для write
#include <stdio.h>  // Для printf
#include <termios.h>
#include <fcntl.h>
#ifdef _WIN32
    // Windows не использует ioctl.h, вместо него можно использовать другие API
#else
    #include <sys/ioctl.h>
#endif

#include <stdlib.h> // Для exit

// Перечисление для цветов
enum colors {
    Fblack = 30,
    Fred,
    Fgreen,
    Fyellow,
    Fblue,
    Fmagenta,
    Fcyan,
    Fgray,
    Fdef = 39,
  
    Bblack = 40,
    Bred,
    Bgreen,
    Byellow,
    Bblue,
    Bmagenta,
    Bcyan,
    Bgray,
    Bdef = 49
  };

// Функции библиотеки
int mt_clrscr(void); // Очистка экрана
int mt_gotoXY(int x, int y); // Перемещение курсора
int mt_getscreensize(int *rows, int *cols); // Получение размера экрана
int mt_setfgcolor(enum colors color); // Установка цвета текста
int mt_setbgcolor(enum colors color); // Установка цвета фона
int mt_setdefaultcolor(void); // Сброс цветов к значениям по умолчанию
int mt_setcursorvisible(int value); // Управление видимостью курсора
int mt_delline(void); // Очистка текущей строки


void printMemoryHex(void);
void printEditableCell(void);
void printAccumulator(void);
void printFlags(void);
void printCounters(void);
void printCommandPanel(void);
#endif