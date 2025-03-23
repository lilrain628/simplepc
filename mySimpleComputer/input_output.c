#include "mySimpleComputer.h"
#include <stdio.h>

// Функция для вывода содержимого одной ячейки памяти в шестнадцатеричном
// формате
void
printCell (int address)
{
  int value;
  if (sc_memoryGet (address, &value))
    {
      printf ("Invalid address.\n");
      return;
    }

  int sign, command, operand;
  if (sc_commandDecode (value, &sign, &command, &operand))
    {
      printf ("Invalid command format.\n");
      return;
    }

  printf ("%04X ", value); // Вывод значения в шестнадцатеричном формате
}

// Функция для вывода содержимого регистра флагов
void
printFlags (void)
{
  int flags[5];
  sc_regGet (FLAG_OVERFLOW, &flags[0]);
  sc_regGet (FLAG_DIVISION_BY_ZERO, &flags[1]);
  sc_regGet (FLAG_MEMORY_ERROR, &flags[2]);
  sc_regGet (FLAG_INVALID_COMMAND, &flags[3]);
  sc_regGet (FLAG_IGNORE_CLOCK, &flags[4]);

  printf ("Flags: %c %c %c %c %c\n", flags[0] ? 'O' : '_',
          flags[1] ? 'D' : '_', flags[2] ? 'M' : '_', flags[3] ? 'I' : '_',
          flags[4] ? 'C' : '_');
}

// Функция для вывода декодированной команды в разных системах счисления
void
printDecodedCommand (int value)
{
  printf ("Decoded command:\n");
  printf ("Decimal: %d\n", value);
  printf ("Octal: %o\n", value);
  printf ("Hexadecimal: %X\n", value);
  printf ("Binary: ");
  for (int i = 15; i >= 0; i--)
    {
      printf ("%d", (value >> i) & 1);
    }
  printf ("\n");
}

// Функция для вывода значения аккумулятора
void
printAccumulator (void)
{
  int value;
  sc_accumulatorGet (&value);
  printf ("Accumulator: %d\n", value);
}

// Функция для вывода значения счетчика команд
void
printCounters (void)
{
  int value;
  sc_icounterGet (&value);
  printf ("Instruction Counter: %d\n", value);
}