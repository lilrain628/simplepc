#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/myBigChars.h"
#include "../include/myTerm.h"
#define OFF 0
#define ON 1
// Память
#define MEMORY_SIZE 128
#define BIGC 36
#define P 0b00000001
#define O 0b00000010
#define M 0b00000100
#define T 0b00001000
#define E 0b00010000
#define MEMORY_MAX_SIZE MEMORY_SIZE
extern int memory[MEMORY_SIZE];
extern int font[BIGC];


int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (const char *filename);
int sc_memoryLoad (const char *filename);

// Регистры
#define FLAG_OVERFLOW 0x1
#define FLAG_DIVISION_BY_ZERO 0x2
#define FLAG_MEMORY_ERROR 0x4
#define FLAG_INVALID_COMMAND 0x8
#define FLAG_IGNORE_CLOCK 0x10

int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);
int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);
int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

// Управление командами
#define COMMAND_MASK 0x7F
#define OPERAND_MASK 0x7F
#define SIGN_MASK 0x80

int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);

void printCell(int address, enum colors fg, enum colors bg);
void printTerm(int address, int input);
void printCommand(void);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);
// Добавьте эти прототипы
void printMemoryHex(void);
void printEditableCell(void);
void printCommandPanel(void);
void in_out(int addresses[5]);
void printBigCell (int address, int bigchars[18][SIZE]);