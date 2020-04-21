#ifndef CLIENT_H
#define CLIENT_H


#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
#include <stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <dirent.h>

void partition(char* path, int num, FILE *fa[], int index);

#endif
