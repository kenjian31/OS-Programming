#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>

void cd(char* arg){
	char buf[1000];
	if (chdir(arg) != 0){
		// printf("%s\n",getcwd(buf, sizeof(buf)));
		perror("cd");
		exit(1);}
	else{
		printf("%s\n", getcwd(buf, sizeof(buf)));
	}

}

int main(int argc, char** argv){
	switch (argc) {
		case 0:
		case 1:
			// cd
			cd(getenv("HOME"));
			break;
		case 2:
			// cd path
			if (strcmp(argv[1],"~") == 0) {
				cd(getenv("HOME"));
			} else {
				cd(argv[1]);
			}
			break;
		default:
			fprintf(stderr, "Too many arguments.");
			exit(1);
	}
	return 0;
}
