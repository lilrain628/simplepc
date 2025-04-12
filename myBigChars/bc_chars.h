#pragma once
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define BOXCHAR_REC "a"
#define BOXCHAR_BR "j"
#define BOXCHAR_BL "m"
#define BOXCHAR_TR "k"
#define BOXCHAR_TL "l"
#define BOXCHAR_VERT "x"
#define BOXCHAR_HOR "q"

#define BYTE 8
#define SIZE 2

int bc_printA (char *str);
int bc_getbigcharpos (int big[SIZE], int x, int y, int *value);
int bc_strlen (char *str);
