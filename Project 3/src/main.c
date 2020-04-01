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

#define OUT_TLB "../bin/tlb_out.txt"
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


	char text[] = "Before virtual address translation of virtual.txt\n\n";
	char text1[] = "After virtual address translation of virtual.tx\n\n";
	FILE * fp = fopen(OUT_TLB, "w");
	if(fp == NULL)
	{
		printf("Read Error\n");
	}
	fprintf(fp, "%s", text);
	fclose(fp);




	print_tlb();
	while((read = getline(&cont,&length,fd)) != -1)
	{
		char* str;
		unsigned int vadd = strtoul(cont, NULL, 16);
		unsigned int vadd_pn = (vadd & 0xfffff000) >> 12;
		int offset = vadd &0xfff;

		// int mem = translate_virtual_address(vadd);


		if(get_tlb_entry(vadd_pn) == -1) {
			populate_tlb(vadd_pn, translate_virtual_address(vadd));
		}

		print_physical_address(translate_virtual_address(vadd), offset);
	}
	printf("Hit rate of the cache is %f\n", get_hit_ratio());
	FILE * fp1 = fopen(OUT_TLB, "a");
	if(fp1 == NULL)
	{
		printf("Read Error\n");
	}
	fprintf(fp1, "%s", text1);
	fclose(fp1);

	print_tlb();

	fclose(fd);
	// Free the page table
	free_resources();
	return 0;
}
