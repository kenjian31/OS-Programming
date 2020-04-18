#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
#include <stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <dirent.h>

void ls(char *path, bool rec) {
    // remove trailing '/'
    if (strlen(path) > 1 && path[strlen(path)-1]=='/')
        path[strlen(path)-1]='\0';
    DIR *dr = opendir(path);
    if (dr == NULL) {
        fprintf(stderr, "Failed to open: %s", path);
        exit(1);
    }
    struct dirent *de = readdir(dr);
    if (!rec) {
        // ls
        while (de != NULL) {
            if (de->d_name[0] != '.')
                printf("%s  ", de->d_name);
            de = readdir(dr);
        }
        printf("\n");
    } else {
        // print path
        printf("%s:\n", path);
        // ls
        ls(path, false);
        printf("\n");
        // print sub dir
        while (de != NULL) {
            if (de->d_name[0] != '.' && de->d_type == DT_DIR) {
                char np[1000];
                sprintf(np,"%s/%s",path,de->d_name);
                ls(np, true);
            }
            de = readdir(dr);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        ls(".", false);
    } else if (argc == 2 || argc == 3) {
        if (strcmp(argv[1], "-R") == 0) {
            // ls -R <path>
            char path[1000] = ".";
            if (argc == 3)
                strcpy(path, argv[2]);
            ls(path, true);
        } else {
            // ls <path>
            if (argc == 3) {
                fprintf(stderr, "Wrong arguments.\n");
                exit(1);
            } else {
                char path[1000];
                strcpy(path, argv[1]);
                ls(path, false);
            }
        }
    } else {
        fprintf(stderr, "Too many arguments.\n");
        exit(1);
    }
}
