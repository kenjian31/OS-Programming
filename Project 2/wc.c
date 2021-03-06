#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

void wc(int mode, char* path){
	 if (path == NULL){	//take input from STDIN
		 		int count_char = 0;
				int count_line = 0;
				int count_word = 0;
				char c;
				int s = 0;
				int i = 0;
				while((c = getchar()) != EOF){
					count_char +=1 ;
				 	if(c == '\n'){
					 	count_line += 1;}
				 	if (!isspace(c) && (s == 0)){
						count_word+=1;
						s = 1;
					}
					else if(isspace(c)){
						 s = 0;
						}
			 }
			 if(mode == 0) {
			 printf("%8d", count_line);
			 printf("%8d", count_word);
			 printf("%8d\n", count_char);}
			 else if (mode == 1){
				 printf("%8d\n", count_line);
			 }
			 else if (mode == 2){
				 printf("%8d\n", count_word);
			 }
			 else if (mode == 3){
				 printf("%8d\n", count_char);
			 }
	}

	else{
	struct stat stat_buf;
	stat(path,&stat_buf);
	//check if path is a directory
	if(S_ISDIR(stat_buf.st_mode)){
		printf("wc: %s: it is a directory\n",path);
		return;
	}

	//check if path is regular file
	else if(S_ISREG(stat_buf.st_mode)){
		FILE* fp = fopen(path,"r");
		if (fp == NULL){
			printf("File can not be open.");
			fclose(fp);
			return;
		}

		if(mode == 1){	//line count
			int count_line = 0;
			char buf[200];
			while(fgets(buf,200,fp) != NULL){
				count_line +=1 ;
			}
			printf("%8d %s\n", count_line, path);
			return;
		}

		else if(mode == 2){	//word count
			int count_word = 0;
			char c;
			int s = 0; // s = 0 represent it is the first space
			while ((c = getc (fp)) != EOF)
			{
					if (!isspace(c) && s == 0){
						count_word+=1;
						s = 1;
					}
					else if(isspace(c)){
						s = 0;
					}
			}
			printf("%8d %s\n", count_word, path);
			return;
		}

		else if (mode == 3){	//char count
			int count_char = 0;
			char c;
			while ((c = fgetc(fp)) != EOF) {
					count_char += 1;
				}
			printf("%8d %s\n", count_char, path);
			return;}


		else if (mode == 0){
			//line count
				int count_line = 0;
				int count_word = 0;
				int count_char = 0;
				char c;
				int s = 0;
				int i = 0;
				while((c = fgetc(fp)) != EOF){
					count_char +=1 ;
					if(c =='\n'){
			 			count_line += 1;}
					if (!isspace(c) && (s == 0)){
								count_word+=1;
								s = 1;
							}
					else if(isspace(c)){
								s = 0;
							}
			}
			printf("%8d", count_line);
			printf("%8d", count_word);
			printf("%8d %s\n", count_char, path);
	}

	//if path is other types
	else{
		perror("Invalid path");
	}
	fclose(fp);
}
}
}


int main(int argc, char** argv){
	if(argc>2){
		if(strcmp(argv[1], "-l") == 0) {
			wc(1, argv[2]);
		} else if(strcmp(argv[1], "-w") == 0) {
			wc(2, argv[2]);
		} else if(strcmp(argv[1], "-c") == 0) {
			wc(3, argv[2]);
		} else {
			printf("Invalid arguments\n");
		}
	} else if (argc==2){
	 	if(strcmp(argv[1], "-l") == 0) {
			wc(1, NULL);
		} else if(strcmp(argv[1], "-w") == 0) {
			wc(2, NULL);
		} else if(strcmp(argv[1], "-c") == 0) {
			wc(3, NULL);
		} else {
    		wc(0, argv[1]);
    	}
  	} else {
  		wc(0,NULL);
  	}

	return 0;
}
