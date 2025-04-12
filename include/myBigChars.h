#pragma once

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "myTerm.h"
#endif

#define BOXCHAR_REC "a"
#define BOXCHAR_BR "j"
#define BOXCHAR_BL "m"
#define BOXCHAR_TR "k"
#define BOXCHAR_TL "l"
#define BOXCHAR_VERT "x"
#define BOXCHAR_HOR "q"

#define BYTE 8
#define SIZE 2

// int bc_printA(char *str);
// int bc_getbigcharpos(int big[SIZE], int x, int y, int *value);
// int bc_strlen(char *str);

int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2, enum colors box_fg,
            enum colors box_bg, char *header, enum colors header_fg,
            enum colors header_bg);
int bc_bigcharread (int fd, int *big, int need_count, int *count);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_getbigcharpos (int big[SIZE], int x, int y, int *value);
int bc_printbigchar (int *big, int x, int y, enum colors fg, enum colors bg);
int bc_setbigcharpos (int big[SIZE], int x, int y, int value);
int bc_strlen (char *str);