#include <stdio.h>

#define PHYSICAL_MEMORY_SIZE 64     // in KB

typedef struct {
    int base;       // base address
    int size;
    int allocated;  // 0 if not allocated, process ID otherwise
} MemoryBlock;

MemoryBlock memory[PHYSICAL_MEMORY_SIZE];  // physical memory blocks
int process_counter = 0;

// initialize memory blocks
void initialize_memory() {
    for (int i = 0; i < PHYSICAL_MEMORY_SIZE; i++) {
        memory[i].base = i;
        memory[i].size = 1;
        memory[i].allocated = 0;
    }
}

// allocate memory
int alloc(int size) {
    int start = -1;
    int count = 0; // number of free blocks
    int free_memory = 0;

    // check if there is enough free memory
    for (int i = 0; i < PHYSICAL_MEMORY_SIZE; i++) {
        if (memory[i].allocated == 0) {
            free_memory++;
        }
    }

    for (int i = 0; i < PHYSICAL_MEMORY_SIZE; i++) {
        if (memory[i].allocated == 0) {  // check if block is free
            if (count == 0) start = i;
            count++;
            if (count == size) {
                for (int j = start; j < start + size; j++) {
                    memory[j].allocated = process_counter;
                }
                printf("Allocated %d KB at base address %d for process %d\n", size, start, process_counter);
                return process_counter++;
            }
        } else {
            count = 0;
        }
    }

    printf("Allocation of %d KB failed for process %d. Remaining memory: %dKB \n", size, process_counter, free_memory);
    return -1;
}

// free memory
void free_memory(int process_id) {
    int found = 0;
    for (int i = 0; i < PHYSICAL_MEMORY_SIZE; i++) {
        if (memory[i].allocated == process_id) {
            memory[i].allocated = 0;
            found = 1;
        }
    }
    if (found) {
        printf("OK: Freed memory for process %d\n", process_id);
    } else {
        printf("Free failed: Process %d not found\n", process_id);
    }
}


int main() {
    initialize_memory();

    //----------------TEST CASES----------------
    char actions[] = {'a', 'a', 'a', 'a', 'f', 'f', 'f'};
    int arguments[] = {12, 24, 8, 128, 1, 7, 2};
    int num_actions = sizeof(actions) / sizeof(actions[0]);
    //------------------------------------------

    for (int i = 0; i < num_actions; i++) {
        if (actions[i] == 'a') {
            alloc(arguments[i]);
        } else if (actions[i] == 'f') {
            free_memory(arguments[i]);
        }
    }

    return 0;
}
