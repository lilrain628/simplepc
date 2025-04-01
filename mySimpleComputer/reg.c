#include "../include/mySimpleComputer.h"
static int accumulator = 0;
static int icounter = 0;
static int flag_register = 0;

int
sc_regInit (void)
{
  flag_register = 0;
  return 0;
}

int
sc_regSet (int reg, int value)
{
  if (reg != FLAG_OVERFLOW && reg != FLAG_DIVISION_BY_ZERO
      && reg != FLAG_MEMORY_ERROR && reg != FLAG_INVALID_COMMAND
      && reg != FLAG_IGNORE_CLOCK)
    {
      return -1;
    }
  if (value)
    {
      flag_register |= reg;
    }
  else
    {
      flag_register &= ~reg;
    }
  return 0;
}

int
sc_regGet (int reg, int *value)
{
  if ((reg != FLAG_OVERFLOW && reg != FLAG_DIVISION_BY_ZERO
       && reg != FLAG_MEMORY_ERROR && reg != FLAG_INVALID_COMMAND
       && reg != FLAG_IGNORE_CLOCK)
      || value == NULL)
    {
      return -1;
    }

  *value = (flag_register & reg) ? 1 : 0;
  return 0;
}

int
sc_accumulatorInit (void)
{
  accumulator = 0;
  return 0;
}

int
sc_accumulatorSet (int value)
{
  if (value < 0xFFFF)
    {
      accumulator = value;
      return 0;
    }
  return -1;
}

int
sc_accumulatorGet (int *value)
{
  if (*value >= 0xFFFF)
    {
      return -1;
    }
  *value = accumulator;
  return 0;
}

int
sc_icounterInit (void)
{
  icounter = 0;
  return 0;
}

int
sc_icounterSet (int value)
{
  if (value < 0xFFFF)
    {
      icounter = value;
      return 0;
    }
  return -1;
}

int
sc_icounterGet (int *value)
{
  if (*value >= 0xFFFF)
    {
      return -1;
    }
  *value = icounter;
  return 0;
}