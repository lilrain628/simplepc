#ifndef MYTERM_H
#define MYTERM_H

#include <unistd.h> // Для write
#include <stdio.h>  // Для printf
#include <sys/ioctl.h> // Для ioctl
#include <stdlib.h> // Для exit

// Перечисление для цветов
enum colors {
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    DEFAULT
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

#endif