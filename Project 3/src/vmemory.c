//Implement the API modeling the translation of virtual page address to a
//physical frame address. We assume a 32 bit virtual memory and physical memory.
//Access to the page table is only via the CR3 register.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vmemory.h"

#define OUT_TLB "../bin/tlb_out.txt"

bool FIFO_policy = true;
int **cr3;

//
// More static functions can be implemented here
//


// The implementation of get_vpage_cr3 is provided in 
// an object file, so no need to re-implement it
void initialize_vmanager(int policy) 
{
	// Set LRU policy when passsed as a parameter
	if (policy)
		FIFO_policy = false;
	cr3 = get_vpage_cr3();
	//printf("cr3: %p\n", cr3);
}

//
// The implementation of following functions is required
//
int translate_virtual_address(unsigned int v_addr)
{
	//TODO
	return -1;
}

void print_physical_address(int frame, int offset)
{
	//TODO
	return;
}

int get_tlb_entry(int n)
{
	//TODO
	return -1;
}

void populate_tlb(int v_addr, int p_addr) 
{
	//TODO
	return;
}

float get_hit_ratio()
{
	//TODO
	return 0.0;
}

//Write to the file in OUT_TLB
void print_tlb()
{
	//TODO
	return;
}
