#include "../include/myTerm.h"
#include "../include/mySimpleComputer.h"
#include "../include/myBigChars.h"
#include <myBigChars.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <time.h>

#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define WHITE_BG "\x1b[47m"
#define WHITE_TEXT "\x1b[37m"
#define BLACK_BG "\x1b[40m"
#define RESET_COLORS "\x1b[0m"

int memory[MEMORY_SIZE];
// Функция для отображения памяти
void printMemoryHex() {
    printf("\x1b[2;1H");  // Перемещаем курсор на 2 строку, 1 столбец

    // Первая ячейка: красный текст на белом фоне
    printf(RED_TEXT WHITE_BG);
    if (memory[0] & 0x8000) {
        printf("-");
    } else {
        printf("+");
    }
    printf("%04X  " RESET_COLORS, memory[0] & 0x7FFF);  // Маска для 16 бит

    // Остальные ячейки: белый текст на черном фоне
    printf(WHITE_TEXT BLACK_BG);
    for (int i = 1; i < MEMORY_SIZE; i++) {
        if (i % 10 == 0) {  // Переход на новую строку каждые 10 ячеек
            printf("\n\x1b[%d;1H", 2 + i / 10);  // Перемещаем курсор на новую строку
        }

        // Проверяем знаковый бит (15-й бит)
        if (memory[i] & 0x8000) {  // Если знаковый бит установлен
            printf("-");  // Отрицательное число
        } else {
            printf("+");  // Положительное число
        }

        // Выводим значение в формате %04X (16-битное шестнадцатеричное число)
        printf("%04X  ", memory[i] & 0xFFFF);  // Маска для 16 бит
    }
    printf(RESET_COLORS "\n");  // Сбрасываем цвета
}

// Функция для отображения редактируемой ячейки
void printEditableCell() {
    printf("\x1b[17;1H");  // Перемещаем курсор на 17 строку, 1 столбец

    printf(RED_TEXT WHITE_BG "Редактируемая ячейка (формат)\n");

    // Получаем значение ячейки как 16-битное число со знаком
    int16_t signed_value = (int16_t)(memory[0] & 0xFFFF);
    // Полное 16-битное представление
    uint16_t unsigned_value = memory[0] & 0x7FFF;

    // Десятичное значение (со знаком)
    printf(WHITE_TEXT BLACK_BG "dec: %d  | ", signed_value);

    // Восьмеричное значение (полное 16-битное представление)
    printf("oct: %6o  | ", unsigned_value);

    // Шестнадцатеричное значение (полное 16-битное представление)
    printf("hex: %04X   | ", unsigned_value);

    // Двоичное значение (все 16 бит)
    printf("bin: ");
    for (int i = 14; i >= 0; i--) {
        printf("%d", (unsigned_value >> i) & 1);
    }
    printf(RESET_COLORS "\n");
}

// Функция для отображения аккумулятора
void printAccumulator() {
    mt_gotoXY(2, 80);  // Позиция для вывода аккумулятора
    printf(RED_TEXT BLACK_BG "Аккумулятор\n");
    mt_setfgcolor(Fdef);
    mt_setbgcolor(Bdef);

    int acc;
    sc_accumulatorGet(&acc);

    mt_gotoXY(3, 75);
    printf("sc: %04X     hex: %04X \n", acc, acc & 0x7FFF);
    mt_setdefaultcolor();
}

// Функция для отображения регистра флагов
void printFlags() {
    mt_gotoXY(2, 110);  // Позиция для вывода флагов
    printf(RED_TEXT BLACK_BG "Регистр флагов\n");
    mt_setfgcolor(Fdef);
    mt_setbgcolor(Bdef);

    int p, zero, m = 0, t, e;
    sc_regGet(FLAG_OVERFLOW, &p);
    sc_regGet(FLAG_DIVISION_BY_ZERO, &zero);
    sc_regGet(FLAG_MEMORY_ERROR, &m);
    sc_regGet(FLAG_INVALID_COMMAND     , &t);
    sc_regGet(FLAG_IGNORE_CLOCK        , &e);

    mt_gotoXY(3, 110);
    printf("%c   %c   %c   %c   %c ",
    p ? 'P' : '_', zero ? '0' : '_', m ? 'M' : '_', t ? 'T' : '_', e ? 'E' : '_');
    printf("\n");
    mt_setdefaultcolor();
}

// Функция для отображения счетчика команд
void printCounters() {
    mt_gotoXY(5, 75);
    printf(RED_TEXT BLACK_BG "Счетчик команд\n");
    mt_setfgcolor(Fdef);
    mt_setbgcolor(Bdef);

    int ic;
    sc_icounterGet(&ic);

    mt_gotoXY(6, 75);
    printf("T:00      IC:%04X \n", ic & 0x7FFF);
    mt_setdefaultcolor();

    mt_gotoXY(30, 1);
}

// Функция для отображения панели "Команда"
void printCommandPanel() {
    int value = 0;
    int sign = 0;
    int command = 0;
    int operand = 0;
    char tmp[12]; // Увеличил размер для безопасности

    sc_icounterGet(&value);
    sc_commandDecode(value, &sign, &command, &operand);

    if (command < 0 || command > 76) {
        snprintf(tmp, sizeof(tmp), "! %02X : %02X", command, operand);
    } else {
        snprintf(tmp, sizeof(tmp), "+ %02X : %02X", command, operand);
    }

    mt_gotoXY(5, 115);
    printf(RED_TEXT BLACK_BG "Команда\n");
    mt_setfgcolor(Fdef);
    mt_setbgcolor(Bdef);

    mt_gotoXY(6, 115);
    printf("%s\n", tmp);

    mt_setdefaultcolor();
    mt_gotoXY(30, 1);
}

void in_out(int addresses[5]) {
    printf("\x1b[20;1H");  // Перемещаем курсор на 20 строку, 1 столбец
    
    // Заголовок: зеленый текст на белом фоне
    printf(GREEN_TEXT WHITE_BG "IN--OUT" RESET_COLORS "\n");
    
    for (int i = 0; i < 5; i++) {
        int address = addresses[i];
        if (address < 0 || address >= MEMORY_SIZE) {
            printf("Адрес %02X недопустим\n", address);
            continue;
        }

        // Получаем значение ячейки памяти
        int16_t value = (int16_t)(memory[address] & 0xFFFF);

        // Определяем знак значения
         char sign = (value & 0x8000) ? '-' : '+';

        // Включаем белый фон только для выводимого текста
        printf(BLACK_BG "%02X> %c%04X" RESET_COLORS "\n", 
               address,sign,  value & 0x7FFF);
    }
}
void printDecodedCommand(int value) {
    int sign, command, operand;

    if (sc_commandDecode(value, &sign, &command, &operand) != 0) {
        printf("Error decoding command\n");
        return;
    }
    
    printf("Decoded command:\n");
    printf("Sign: %s\n", sign ? "-" : "+");
    printf("Command: %d (0x%X)\n", command, command);
    printf("Operand: %d (0x%X)\n", operand, operand);  // Исправлен формат вывода
}

void printBigCell(int address, int bigchars[18][SIZE])
{
    int value = 0;
    int sign = 0;
    int command = 0;
    int operand = 0;

    bc_box(62, 7, 107, 18, Fdef, Bdef, "Редактируемая ячейка (увеличено)", Fred, Bgray);

    sc_memoryGet(address, &value);

    // Попробуем декодировать, если команда корректна
    // if ((value & 0x7FFF) != 0 && sc_commandDecode(value, &sign, &command, &operand) == 0) {
    //     // ok, значения получены
    // } else {
    //     // если невалидная команда — просто показываем знак и обнуляем команду/операнд
    //     sign = value >> 15;
    //     command = 0;
    //     operand = 0;
    // }

    // Знак
    if (sign == 1) {
        bc_printbigchar(bigchars[17], 9, 77, Fdef, Bdef); // '-'
    } else {
        bc_printbigchar(bigchars[16], 9, 77, Fdef, Bdef); // '+'
    }

    // Выделим цифры для вывода
    int command1 = (command >> 4) & 0x0F;
    int command2 = command & 0x0F;
    int operand1 = (operand >> 4) & 0x0F;
    int operand2 = operand & 0x0F;

    // Выводим большие символы команды и операнда
    bc_printbigchar(bigchars[1], 9, 90, Fdef, Bdef);
    bc_printbigchar(bigchars[command2], 9, 99, Fdef, Bdef);
    bc_printbigchar(bigchars[operand1], 9, 108, Fdef, Bdef);
    bc_printbigchar(bigchars[operand2], 9, 117, Fdef, Bdef);

    // Подпись под ячейкой
    char buf[100];
    mt_gotoXY(63, 17);
    sprintf(buf, "\033[0;%dmНомер редактируемой ячейки: %d", Fblue, address);
    write(1, buf, strlen(buf));

    // Отладочная информация
    if (sign == 1)
        printf("DEBUG: value = -%04X, command = %02X, operand = %02X\n", value & 0x7FFF, command, operand);
    else
        printf("DEBUG: value = +%04X, command = %02X, operand = %02X\n", value & 0x7FFF, command, operand);
}




// void
// printBigCell (int address, int bigchars[18][SIZE])
// {
//   int value = 0;
//   int sign = 0;
//   int command = 0;
//   int operand = 0;
  
//   bc_box (62, 7, 107, 18, Fdef, Bdef, "Редактируемая ячейка (увеличено)", Fred,
//           Bgray);

//   sc_memoryGet (address, &value);
//   //sc_commandDecode (value, &sign, &command, &operand);

//   if (sign == 1)
//     {
//       bc_printbigchar (bigchars[17], 9, 63, Fdef, Bdef);
//     }
//   else
//     {
//       bc_printbigchar (bigchars[16], 9, 75, Fdef, Bdef);
//     }

//   int command1 = command >> 4;
//   command = command & 0x0f;

//   int operand1 = operand >> 4;
//   operand = operand & 0x0f;

//   bc_printbigchar (bigchars[command1], 9, 90, Fdef, Bdef);
//   bc_printbigchar (bigchars[command], 9, 99, Fdef, Bdef);
//   bc_printbigchar (bigchars[operand1], 9, 108, Fdef, Bdef);
//    bc_printbigchar (bigchars[operand], 9, 117, Fdef, Bdef);
//   char buf[100];
//   mt_gotoXY (63, 17);
//   sprintf (buf, "\033[0;%dmНомер редактируемой ячейки: %d", Fblue, address);
  
//   if (sign == 1)
//     printf("DEBUG: value = -%04X, command = %02X, operand = %02X\n", value & 0x7FFF, command, operand);
// else
//     printf("DEBUG: value = +%04X, command = %02X, operand = %02X\n", value & 0x7FFF, command, operand);

//   write (1, buf, strlen (buf));
// }
