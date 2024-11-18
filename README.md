# Memory Translator Lab (Lab 5)

## Project Overview
This project implements a memory management system based on the **Memory Translator Lab** requirements. It consists of three tasks:
1. **Pagination Address Translator** (`mmu-pagination.c`)
2. **Segmentation Address Translator** (`mmu-segmentation.c`)
3. **Base and Bounds Memory Allocator** (`basebounds-allocator.c`)

The project demonstrates memory management techniques such as **paging**, **segmentation**, and **base and bounds allocation**.

## Directory Structure
```
<gomes>-lab5.zip
├── basebounds-allocator.c
├── mmu-pagination.c
├── mmu-segmentation.c
└── README.md
```

## Compilation Instructions
Each file can be compiled using `gcc`. Below are the commands for compiling each program:

### Task 1: Pagination Address Translator
```bash
gcc mmu-pagination.c -o mmu-pagination
```

### Task 2: Segmentation Address Translator
```bash
gcc mmu-segmentation.c -o mmu-segmentation
```

### Task 3: Base and Bounds Memory Allocator
```bash
gcc basebounds-allocator.c -o basebounds-allocator
```

## Usage
Below are the instructions for running each program.

### Task 1: Pagination Address Translator
This program translates virtual addresses to physical addresses using a **paging** scheme.

#### Input:
- A predefined page table array.
- A list of virtual addresses to be translated.

#### Example Run:
```bash
./mmu-pagination
```

#### Example Output:
```
VA 0x00003229 (decimal: 12841) --> 0x00006229 (decimal: 25129) [VPN 3]
VA 0x00001369 (decimal: 4969) --> Invalid (VPN 1 not valid)
VA 0x00001e80 (decimal: 7808) --> Invalid (VPN 1 not valid)
```

### Task 2: Segmentation Address Translator
This program translates virtual addresses using a **segmentation** scheme.

#### Input:
- A segment table base array.
- A segment table bounds array.
- A list of virtual addresses to be translated.

#### Example Run:
```bash
./mmu-segmentation
```

#### Example Output:
```
VA 0x0000000c (decimal: 12) --> VALID in SEG1: 0x00000020 (decimal: 32)
VA 0x00000008 (decimal: 8) --> VALID in SEG0: 0x00000032 (decimal: 50)
VA 0x00000007 (decimal: 7) --> SEGMENTATION VIOLATION (SEG0)
```

### Task 3: Base and Bounds Memory Allocator
This program implements a memory allocator using the **base and bounds** method with a choice of allocation strategies (first-fit, best-fit, worst-fit).

#### Input:
- Allocation method. Change at the top of the code. 0 - first fit, 1 - best fit, 2 worst fit.
- List of actions (`'a'` for alloc, `'f'` for free).
- List of arguments corresponding to the actions (size for alloc, process ID for free).

#### Example Run:
```bash
./basebounds-allocator
```

#### Example Output:
```
Allocated 12 KB at base address 0 for process 0
Allocated 24 KB at base address 12 for process 1
OK: Freed memory for process 1
Allocated 16 KB at base address 36 for process 2
Allocated 8 KB at base address 52 for process 3
OK: Freed memory for process 0
OK: Freed memory for process 3
```

## What works:
All tasks in the project have been implemented and tested successfully:
- **Task 1 (Pagination Address Translator):** Properly translates virtual addresses to physical addresses using a predefined page table. It handles invalid pages correctly.
- **Task 2 (Segmentation Address Translator):** Correctly translates virtual addresses using segmentation. It handles segmentation violations and outputs the expected results.
- **Task 3 (Base and Bounds Memory Allocator):** Successfully allocates and frees memory using the base and bounds method. It implements a first-fit strategy and manages the process IDs accurately.


## Authors
This laboratory was made by [Ana Gomes](https://github.com/anouillz) for the Operating Systems class at HESSO Valais/Wallis.
