//main.c program to translate the virtual addresses from the virtual.txt
//into the physical frame address. Project 3 - CSci 4061
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include "vmemory.h"

#define INPUT_FILE "../bin/virtual.txt"
#define MSB_20BITS 0xfffff000

int main(int argc, char* argv[])
{
	if (argc > 2) {
		printf("Too many arguments, enter up to one argument\n");
		exit(-1);
	}

	int policy = (argc == 2) ? 1:0;
	initialize_vmanager(policy);

	//TODO: Fill the algorithm by reading from INPUT_FILE


	FILE * fd = fopen(INPUT_FILE, "r");
	if (fd == NULL)
	{
		printf("Read file error\n");
		return 0;
	}
	char* cont = NULL;
	size_t length = 0;
	ssize_t read;
	while((read = getline(&cont,&length,fd)) != -1)
	{
		char* str;
		unsigned int vadd = strtoul(cont, NULL, 16);
		unsigned int vadd_pn = (vadd & 0xfffff000) >> 12;
		int offset = vadd & 0xffff00000;

		print_tlb();
		print_physical_address(1, offset);
		if(get_tlb_entry(vadd_pn) == -1) {
			populate_tlb(vadd_pn, translate_virtual_address(vadd));
		}
	}
	fclose(fd);
	// Free the page table
	free_resources();
	return 0;
}
