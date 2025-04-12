#include "bc_chars.h"
#include "../include/myTerm.h"
#include "myBigChars.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int bc_bigcharread(int fd, int *big, int need_count, int *count) {
    if (big == NULL || count == NULL) {
        return -1;
    }

    *count = read(fd, big, need_count * sizeof(int) * SIZE) / (sizeof(int) * SIZE);
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count) {
    if (big == NULL) {
        return -1;
    }

    ssize_t n = write(fd, big, count * sizeof(int) * SIZE);
    return n == -1 ? -1 : 0;
}

int bc_box(int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
           char *header, enum colors header_fg, enum colors header_bg) {
    int tmp, maxx, maxy, i;
    int len_utf = bc_strlen(header);
    int len_asc = strlen(header);

    if (x1 > x2) { tmp = x1; x1 = x2; x2 = tmp; }
    if (y1 > y2) { tmp = y1; y1 = y2; y2 = tmp; }

    mt_getscreensize(&maxy, &maxx);
    mt_setbgcolor(box_bg);
    mt_setfgcolor(box_fg);
    if ((x1 < 0) || (y1 < 0) || (x2 > maxx) || (y2 > maxy) || (x2 - x1 < 2) || (y2 - y1 < 2))
        return -1;

    mt_gotoXY(x1, y1);
    bc_printA(BOXCHAR_TL);
    for (i = x1 + 1; i < x2; i++) bc_printA(BOXCHAR_HOR);
    bc_printA(BOXCHAR_TR);

    for (i = y1 + 1; i < y2; i++) {
        mt_gotoXY(x1, i); bc_printA(BOXCHAR_VERT);
        mt_gotoXY(x2, i); bc_printA(BOXCHAR_VERT);
    }

    mt_gotoXY(x1, y2);
    bc_printA(BOXCHAR_BL);
    for (i = x1 + 1; i < x2; i++) bc_printA(BOXCHAR_HOR);
    bc_printA(BOXCHAR_BR);

    mt_setfgcolor(header_fg);
    mt_setbgcolor(header_bg);
    mt_gotoXY(x1 + 1 + ((x2 - x1) / 2) - (len_utf + 1) / 2, y1);
    write(STDOUT_FILENO, header, len_asc);
    mt_setdefaultcolor();
    return 0;
}

int bc_printA(char *str) {
    int term = open("/dev/tty", O_RDWR);
    if (term == -1) {
        return -1;
    }
    char buf[8];
    sprintf(buf, "\E(0%s\E(B", str);
    write(term, buf, strlen(buf));
    close(term);
    return 0;
}


int
bc_printbigchar (int bigchar[SIZE], int x, int y, enum colors fg,
                 enum colors bg)
{
  int rows = 0;
  int cols = 0;

  mt_getscreensize (&rows, &cols);

  // if (x + BYTE > cols || y + BYTE > rows || bigchar == NULL)
  //   {
  //     return -1;
  //   }

  mt_gotoXY (x, y);
  mt_setbgcolor (bg);
  mt_setfgcolor (fg);

  for (int i = 0; i < SIZE * sizeof (int); i++)
    {
      for (int j = 0; j < BYTE; j++)
        {
          int flag = 0;
          bc_getbigcharpos (bigchar, j, i, &flag);

          if (flag == 1)
            {
              mt_gotoXY (x + j, y + i);
              bc_printA (BOXCHAR_REC);
            }
          else
            {
              mt_gotoXY (x + j, y + i);
              bc_printA (" ");
            }
        }
    }
  mt_setdefaultcolor ();
  return 0;
}

int
bc_setbigcharpos (int big[SIZE], int x, int y, int value)
{
  if (big == NULL)
    {
      return -1;
    }

  if (value == 0)
    {
      big[y / 4] = big[y / 4] & ~(1 << (x + ((y % 4) * BYTE)));
    }
  else
    {
      big[y / 4] = big[y / 4] | (1 << (x + ((y % 4) * BYTE)));
    }
  return 0;
}

int
bc_strlen (char *str)
{
  int count = 0;
  while (*str != '\0')
    {
      if ((*str) < 0x80 && *str >= 0)
        {
          count++;
          str++;
        }
      else if (((*str) & 0x7f) <= 0x5f && ((*str) & 0x7f) >= 0x40)
        {
          count++;
          str += 2;
        }
      else if (((*str) & 0x7f) <= 0x6f && ((*str) & 0x7f) >= 0x60)
        {
          count++;
          str += 3;
        }
      else if (((*str) & 0x7f) <= 0x77 && ((*str) & 0x7f) >= 0x70)
        {
          count++;
          str += 4;
        }
      else
        {
          return 0;
        }
    }

  return count;
}

int
bc_getbigcharpos (int big[SIZE], int x, int y, int *value)
{
  if (value == NULL || big == NULL)
    {
      return -1;
    }

  *value = (big[y / sizeof (int)] >> (x + ((y % 4) * BYTE))) & 1;
  return 0;
}

