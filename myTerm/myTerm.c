#include "myTerm.h"
#include "../include/mySimpleComputer.h"
// Очистка экрана и перемещение курсора в левый верхний угол
int mt_clrscr(void) {
    if (write(STDOUT_FILENO, "\033[H\033[J", 6) == -1) {
        return -1;
    }
    return 0;
}

// Перемещение курсора в позицию (x, y)
int mt_gotoXY(int x, int y) {
    char buffer[32];
    int len = snprintf(buffer, sizeof(buffer), "\033[%d;%dH", x, y);
    if (write(STDOUT_FILENO, buffer, len) == -1) {
        return -1;
    }
    return 0;
}

// Получение размера экрана
int mt_getscreensize(int *rows, int *cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return -1;
    }
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
}

// Установка цвета текста
int mt_setfgcolor(enum colors color) {
    if (color < BLACK || color > DEFAULT) {
        return -1;
    }
    char buffer[16];
    int len = snprintf(buffer, sizeof(buffer), "\033[3%dm", color);
    if (write(STDOUT_FILENO, buffer, len) == -1) {
        return -1;
    }
    return 0;
}

// Установка цвета фона
int mt_setbgcolor(enum colors color) {
    if (color < BLACK || color > DEFAULT) {
        return -1;
    }
    char buffer[16];
    int len = snprintf(buffer, sizeof(buffer), "\033[4%dm", color);
    if (write(STDOUT_FILENO, buffer, len) == -1) {
        return -1;
    }
    return 0;
}

// Сброс цветов к значениям по умолчанию
int mt_setdefaultcolor(void) {
    if (write(STDOUT_FILENO, "\033[0m", 4) == -1) {
        return -1;
    }
    return 0;
}

// Управление видимостью курсора
int mt_setcursorvisible(int value) {
    if (value) {
        if (write(STDOUT_FILENO, "\033[?25h", 6) == -1) {
            return -1;
        }
    } else {
        if (write(STDOUT_FILENO, "\033[?25l", 6) == -1) {
            return -1;
        }
    }
    return 0;
}

// Очистка текущей строки
int mt_delline(void) {
    if (write(STDOUT_FILENO, "\033[2K", 4) == -1) {
        return -1;
    }
    return 0;
}