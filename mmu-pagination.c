#include <stdio.h>

#define ADDRESS_SPACE_SIZE 16 // in KB
#define PHYSICAL_MEMORY_SIZE 64 // in KB
#define PAGE_SIZE 4 // in KB


//---------TEST CASES----------------
// page table
unsigned int page_table[] = {0x8000000c, 0x00000000, 0x00000000, 0x80000006};
// virtual addresses
unsigned int virtual_addresses[] = {
        0x00003229, 0x00001369, 0x00001e80, 0x00002556, 0x00003a1e
};

// convert virtual address to physical address using paging
void translate_address(unsigned int va) {
    unsigned int vpn = va / (PAGE_SIZE * 1024); // calculate VPN
    unsigned int offset = va % (PAGE_SIZE * 1024); // calculate offset

    if (vpn >= sizeof(page_table) / sizeof(page_table[0])) {
        printf("VA 0x%08x (decimal: %u) --> Invalid (VPN %u out of range)\n", va, va, vpn);
        return;
    }

    unsigned int pfn = page_table[vpn];
    if (pfn == 0x00000000) {
        printf("VA 0x%08x (decimal: %u) --> Invalid (VPN %u not valid)\n", va, va, vpn);
        return;
    }

    // extract PFN from page table entry
    pfn &= 0x0000000f;
    unsigned int physical_address = (pfn * PAGE_SIZE * 1024) + offset;

    printf("VA 0x%08x (decimal: %u) --> 0x%08x (decimal: %u) [VPN %u]\n",
           va, va, physical_address, physical_address, vpn);
}

int main() {
    // get size of virtual addresses
    int num_addresses = sizeof(virtual_addresses) / sizeof(virtual_addresses[0]);

    // translate each virtual address
    for (int i = 0; i < num_addresses; i++) {
        translate_address(virtual_addresses[i]);
    }

    return 0;
}

