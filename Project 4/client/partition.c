#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
#include <stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <dirent.h>

#define MAX_PATH_LEN (256)

void partition(char* path, int num, FILE *fa[], int index) {
    DIR *d = NULL;
    struct dirent *dp = NULL;
    struct stat st;
    char p[MAX_PATH_LEN] = {0};

    // FILE *fp = fopen("ClientInput/Client.txt", "a+");


    if(stat(path, &st) < 0 || !S_ISDIR(st.st_mode)) {
        printf("invalid path: %s\n", path);
        return;
    }

    if(!(d = opendir(path))) {
        printf("opendir[%s] error: %m\n", path);
        return;
    }

    while((dp = readdir(d)) != NULL) {
        if((!strncmp(dp->d_name, ".", 1)) || (!strncmp(dp->d_name, "..", 2)))
            continue;

            strcpy(p, path);
            strcat(p, "/");
            strcat(p, dp->d_name);
            stat(p, &st);
        if(!S_ISDIR(st.st_mode)) {
            // printf("%s\n", p);
            fprintf(fa[index], "%s\n",p);
            index++;
            if(index == num)
            {
              index = 0;
            }
        }
         else {
            partition(p,num, fa, index);
        }
    }

    closedir(d);

    return;
}

int main(int argc, char *argv[])
{
  char path[1000] = ".";
  if (argc < 2) {
    fprintf(stderr, "Wrong arguments.\n");
    exit(1);

    }
 else {
    strcpy(path,argv[1]);
    int num = atoi(argv[2]);
    int index = 1;

    if (path[strlen(path)-1]=='/')
    {
      path[strlen(path)-1]='\0';
    }

    char * dirname = "ClientInput";
    mkdir(dirname, 0777);

    // path[strlen(path)-1] = '\0';
    FILE *fa[num];
    for (int i = 0; i < num; i++)
    {
        char filename[20];
        sprintf(filename, "ClientInput/Client%d.txt", i+1);
        fa[i] = fopen(filename, "w+");
    }

    partition(path,num, fa, index);

    for(int i = 0; i < num; i++)
    {
      fclose(fa[i]);
    }
    }
    return 0;
}
