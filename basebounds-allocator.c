#include <stdio.h>


#define MEMORY_SIZE 64  // physical memory size in KB
#define MAX_PROCESSES 64
#define ALLOC_METHOD 0  // 0 = First-Fit, 1 = Best-Fit, 2 = Worst-Fit

// memory block structure
typedef struct {
    int base;
    int size;
    int is_free;
} Block;

Block memory[MEMORY_SIZE];          // array of memory blocks
int num_blocks = 1;
int process_bases[MAX_PROCESSES];
int process_sizes[MAX_PROCESSES];

// initialize memory
void initialize_memory() {
    memory[0].base = 0;
    memory[0].size = MEMORY_SIZE;
    memory[0].is_free = 1;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        process_bases[i] = -1; // initialize process bases to -1 (unallocated), process ID if allocated
        process_sizes[i] = 0;  // initialize process sizes to 0
    }
}


int first_fit(int size) {
    for (int i = 0; i < num_blocks; i++) {
        // find the first free block that fits the process
        if (memory[i].is_free && memory[i].size >= size) {
            int base = memory[i].base;
            memory[i].base += size;
            memory[i].size -= size;
            if (memory[i].size == 0) {
                memory[i] = memory[num_blocks - 1];
                num_blocks--;
            }
            return base;
        }
    }
    return -1;
}

int best_fit(int size) {
    int best_index = -1;
    int min_size = MEMORY_SIZE + 1;
    for (int i = 0; i < num_blocks; i++) {
        // find the smallest free block that fits the process
        if (memory[i].is_free && memory[i].size >= size && memory[i].size < min_size) {
            best_index = i;
            min_size = memory[i].size;
        }
    }
    if (best_index != -1) {
        int base = memory[best_index].base;
        memory[best_index].base += size;
        memory[best_index].size -= size;
        if (memory[best_index].size == 0) {
            memory[best_index] = memory[num_blocks - 1];
            num_blocks--;
        }
        return base;
    }
    return -1;
}

int worst_fit(int size) {
    int worst_index = -1;
    int max_size = -1;
    // find the largest free block that fits the process
    for (int i = 0; i < num_blocks; i++) {
        if (memory[i].is_free && memory[i].size >= size && memory[i].size > max_size) {
            worst_index = i;
            max_size = memory[i].size;
        }
    }
    if (worst_index != -1) {
        int base = memory[worst_index].base;
        memory[worst_index].base += size;
        memory[worst_index].size -= size;
        if (memory[worst_index].size == 0) {
            memory[worst_index] = memory[num_blocks - 1];
            num_blocks--;
        }
        return base;
    }
    return -1;
}

int allocate(int size, int process_id) {
    int base;
    switch (ALLOC_METHOD) {
        case 0:
            base = first_fit(size);
            break;
        case 1:
            base = best_fit(size);
            break;
        case 2:
            base = worst_fit(size);
            break;
        default:
            return -1;
    }
    if (base != -1) {
        process_bases[process_id] = base;
        process_sizes[process_id] = size;
        printf("Process %d: Allocated %d KB at base address %d KB\n", process_id, size, base);
        return base;
    }
    printf("Process %d: Allocation error\n", process_id);
    return -1;
}

// Free memory for a given process
void free_memory(int process_id) {
    int base = process_bases[process_id];
    int size = process_sizes[process_id];
    if (base == -1) {
        printf("Process %d not allocated\n", process_id);
        return;
    }
    // Add the freed block back to memory as a free block
    memory[num_blocks].base = base;
    memory[num_blocks].size = size;
    memory[num_blocks].is_free = 1;
    num_blocks++;
    process_bases[process_id] = -1;
    process_sizes[process_id] = 0;
    printf("OK: Freed memory for process %d\n", process_id);
}

// process the actions - allocation and freeing of memory
void process_actions(char actions[], int arguments[], int num_actions) {
    for (int i = 0; i < num_actions; i++) {
        if (actions[i] == 'a') {
            int size = arguments[i];
            allocate(size, i);
        } else if (actions[i] == 'f') {
            int process_id = arguments[i];
            free_memory(process_id);
        }
    }
}

int main() {
    initialize_memory();

    // ----------- TEST CASES 1------------
    /*
    // basic tests
    char actions[] = {'a', 'a', 'f', 'a', 'a', 'f', 'f'};
    int arguments[] = {12, 24, 1, 16, 8, 0, 3};
    int num_actions = sizeof(actions) / sizeof(actions[0]);
    */
    // ----------- TEST CASES 2------------

    // check exceeding memory size
    // check no process allocated
    char actions[] = {'a', 'a', 'f', 'a', 'a', 'f', 'f', 'a', 'f'};
    int arguments[] = {24, 4, 0, 16, 8, 1, 3, 32, 6};
    int num_actions = sizeof(actions) / sizeof(actions[0]);


    process_actions(actions, arguments, num_actions);

    return 0;
}
