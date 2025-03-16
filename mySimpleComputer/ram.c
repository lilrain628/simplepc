#include "mySimpleComputer.h"
static int memory[128];

int sc_memoryInit (void){
    for (int i = 0; i < 128; i++) {
        memory[i] = 0; 
    }
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address >= MEMORY_SIZE) {
        return -1;  
    }
    memory[address] = value;
    return 0;
}
int sc_memoryGet(int address, int *value) {
    if (address < 0 || address >= MEMORY_SIZE || value == NULL) {
        return -1; 
    }
    *value = memory[address];
    return 0;
}
int sc_memorySave(const char *filename) {
    if (filename == NULL) {
        return -1;  
    }

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return -1;  
    }

    size_t written = fwrite(memory, sizeof(int), MEMORY_SIZE, file);
    fclose(file);

    if (written != MEMORY_SIZE) {
        return -1;  
    }
    return 0;
}


int sc_memoryLoad(const char *filename) {
    if (filename == NULL) {
        return -1;  
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;  
    }

    int temp_memory[MEMORY_SIZE];
    size_t read = fread(temp_memory, sizeof(int), MEMORY_SIZE, file);
    fclose(file);

    if (read != MEMORY_SIZE) {
        return -1;  
    }

    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = temp_memory[i];
    }
    return 0;
}
