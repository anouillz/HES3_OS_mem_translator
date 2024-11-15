//
// Created by Ana Goncalves on 15.11.2024.
//

#include <stdio.h>
#include <stdint.h>

#define ADDRESS_SPACE_SIZE 16    // Address space size in K
#define PHYSICAL_MEMORY_SIZE 64  // Physical memory size in K
#define SEGMENT_BIT 3            // needed to extract 4th bit from right

//------------TEST CASES----------------
// segment base table (in hexadecimal)
uint32_t segment_base[] = {0x0000031, 0x00000020}; // uint32_t to store 32 bits - physical address can be large
// segment limit table
uint16_t segment_limit[] = {4, 5};
// virtual address to translate (in hexadecimal)
uint32_t virtual_addresses[] = {0x0000000c, 0x00000008, 0x00000001, 0x00000007, 0x00000000};
// virtual address (in decimal)
uint32_t virtual_addresses_decimal[] = {12, 8, 1, 7, 0};


// extract segment number from virtual address
int get_segment_number(uint32_t virtual_address) {
    return (virtual_address >> SEGMENT_BIT) & 1;  // Extract the 4th bit (5th position, index 4)
}


// translate virtual address to physical address
void translate_address(uint32_t virtual_address, uint32_t virtual_address_decimal) {
    // check if the virtual address exceeds the address space size
    if (virtual_address >= (ADDRESS_SPACE_SIZE * 1024)) {
        printf("VA 0x%08x (decimal: %5u) --> ADDRESS SPACE VIOLATION\n",
               virtual_address, virtual_address_decimal);
        return;
    }

    int segment_number = get_segment_number(virtual_address);
    uint32_t offset = virtual_address % 16;  // extract lower 4 bits using modulo

    // check if the offset exceeds the segment limit
    if (offset >= segment_limit[segment_number]) {
        printf("VA 0x%08x (decimal: %5u) --> SEGMENTATION VIOLATION (SEG%d)\n",
               virtual_address, virtual_address_decimal, segment_number);
        return;
    }

    // calculate physical address
    uint32_t physical_address = segment_base[segment_number] + offset;

    // check if physical address exceeds physical memory size
    if (physical_address >= (PHYSICAL_MEMORY_SIZE * 1024)) {
        printf("VA 0x%08x (decimal: %5u) --> PHYSICAL MEMORY VIOLATION\n",
               virtual_address, virtual_address_decimal);
    } else {
        printf("VA 0x%08x (decimal: %5u) --> VALID in SEG%d: 0x%08x (decimal: %5u)\n",
               virtual_address, virtual_address_decimal, segment_number, physical_address, physical_address);
    }
}

int main() {
    int num_addresses = sizeof(virtual_addresses) / sizeof(virtual_addresses[0]);

    // translate each virtual address
    for (int i = 0; i < num_addresses; i++) {
        translate_address(virtual_addresses[i], virtual_addresses_decimal[i]);
    }

    return 0;
}
