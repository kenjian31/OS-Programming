#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>

void cd(char* arg){
	if (chdir(arg) != 0){
		char buf[100];
		printf("1111");
		printf("%s\n",getcwd(buf, sizeof(buf)));
		perror("bash: cd");}
	else{
		char buf[100];
		chdir(arg);
		getcwd(buf, sizeof(buf));
		printf("%s\n", buf);
	}

}

int main(int argc, char** argv){

	if(argc<2){
		printf("Pass the path as an argument\n");
		return 0;
	}
	cd(argv[1]);
	return 0;
}
