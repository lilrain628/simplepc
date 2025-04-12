#include "myTerm.h"
#include "../include/mySimpleComputer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
#endif

// Очистка экрана и перемещение курсора в левый верхний угол
int mt_clrscr(void) {
    printf("\033[H\033[J");
    fflush(stdout);
    return 0;
}

// Перемещение курсора в позицию (x, y)
int mt_gotoXY(int x, int y) {
    printf("\033[%d;%dH", x, y);
    fflush(stdout);
    return 0;
}

// Получение размера экрана (кроссплатформенно)
int mt_getscreensize(int *rows, int *cols) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return -1;
    }
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return -1;
    }
    *rows = ws.ws_row;
    *cols = ws.ws_col;
#endif
    return 0;
}

// Установка цвета текста
int mt_setfgcolor(enum colors color) {
    if (color < Bdef || color > Fdef) {
        return -1;
    }
    printf("\033[3%dm", color);
    fflush(stdout);
    return 0;
}

// Установка цвета фона
int mt_setbgcolor(enum colors color) {
    if (color < Bdef || color > Fdef) {
        return -1;
    }
    printf("\033[4%dm", color);
    fflush(stdout);
    return 0;
}

// Сброс цветов к значениям по умолчанию
int mt_setdefaultcolor(void) {
    printf("\033[0m");
    fflush(stdout);
    return 0;
}

// Управление видимостью курсора
int mt_setcursorvisible(int value) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = value;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#else
    if (value) {
        printf("\033[?25h");
    } else {
        printf("\033[?25l");
    }
    fflush(stdout);
#endif
    return 0;
}

// Очистка текущей строки
int mt_delline(void) {
    printf("\033[2K");
    fflush(stdout);
    return 0;
}