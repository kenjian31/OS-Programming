#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <limits.h>
#include <fcntl.h>

#include "util.h"

void run(char *token, char *root) {
	// write(STDOUT_FILENO, "Running: ", 9);
	// write(STDOUT_FILENO, token, strlen(token));
	// write(STDOUT_FILENO, "\n", 1);
	char *cmd = NULL;
	char *file = NULL;
	int file_mode = 0;
	int token_len = strlen(token);
	char *args[_POSIX_ARG_MAX];
	int fd;
	cmd = strtok(token, ">");
	file = strtok(NULL, "");
	if (file != NULL) {
		if (file[0] != '>'){
			file_mode = 1;
		} else {
			file += 1;
			file_mode = 2;
		}
		file = trimwhitespace(file);
	}
	if (strlen(cmd)+1==token_len || (file_mode != 0 && file[0] == '\0')) {
		write(STDERR_FILENO, "File not provided\n", 18);
		exit(1);
	}
	if (file_mode == 2) {
		fd = open(file, O_CREAT|O_APPEND|O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	} else if (file_mode == 1) {
		fd = open(file, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}

	parse_line(cmd, args, " ");
	char exe[_POSIX_ARG_MAX+strlen(root)+1];
	enum command_type cmd_type;
	cmd_type = get_command_type(args[0]);

	switch (cmd_type) {
		case EXIT:
			exit(100);
		case CD:
			exit(101);
		case LS:
		case WC:
			strcpy(exe, root);
			strcat(exe, "/");
		default:
			strcat(exe, args[0]);
			if (execvp(exe, args)==-1) {
				write(STDERR_FILENO, "Command not found: ", 19);
				write(STDERR_FILENO, args[0], strlen(args[0]));
				write(STDERR_FILENO, "\n", 1);
			}
	}
	return;
}

void finish(int status, char *token, char *prev){
	switch (status) {
		case 100: 
			exit(0);
		case 101:
			// change directory
			strtok(token, " ");
			char *dir = strtok(NULL, "");
			if ((dir == NULL) || dir[0] == '\0' || dir[0] == '~') {
				chdir(getenv("HOME"));
			} else if (dir[0] == '-') {
				chdir(prev);
			} else if (chdir(dir) != 0) {
				write(STDERR_FILENO, "No such file or directory: ", 27);
				write(STDERR_FILENO, dir, strlen(dir));
				write(STDERR_FILENO, "\n", 1);
			}
		default:
			return;
	}
}

int main(){
	char input[_POSIX_ARG_MAX];
	ssize_t input_len;
	char *token1 = NULL;
	char *token2 = NULL;
	int status1 = 0;
	int status2 = 0;
	char path[FILENAME_MAX];
	char root[FILENAME_MAX];
	char prev[FILENAME_MAX];
	char temp[FILENAME_MAX];
	if (getcwd(root, FILENAME_MAX) == NULL) {
			write(STDERR_FILENO, "Unable to get current directory, exiting...\n", 44);
			exit(1);
		}
	strcpy(prev, root);
	while(true){
		// print current directory
		if (getcwd(path, FILENAME_MAX) == NULL) {
			write(STDERR_FILENO, "Unable to get current directory, exiting...\n", 44);
			exit(1);
		}
		write(STDOUT_FILENO,"[4061-shell]",12);
		write(STDOUT_FILENO, path, strlen(path));
		write(STDOUT_FILENO, " $", 2);

		// read input
		input_len = read(STDIN_FILENO, input, _POSIX_ARG_MAX);
		if (input_len < 0) {
			write(STDERR_FILENO,"Unable to read from STDIN, exiting...\n", 38);
			exit(1);
		} else if (input_len == _POSIX_ARG_MAX) {
			write(STDERR_FILENO,"Input is too long\n", 18);
			input[0]='\0';
		} else {
			input[input_len>0?input_len-1:0]='\0';
		}

		// parse input
		// write(STDOUT_FILENO, input, strlen(input));
		token1 = strtok(input, "|");
		if (token1 != NULL)
			token1 = trimwhitespace(token1);
		token2 = strtok(NULL, "");
		if (token2 != NULL)
			token2 = trimwhitespace(token2);

		// fork & exec | handle error | exit
		if (token1 != NULL && token2 == NULL) {
			if (fork()==0) {
				run(token1, root);
				exit(0);
			}
			wait(&status1);
			finish(WEXITSTATUS(status1), token1, prev);
		} else if (token1 != NULL && token2 != NULL) {
			int fd[2];
    		pipe(fd);
			if (fork()==0) {
				close(fd[0]);
				dup2(fd[1],STDOUT_FILENO);
				close(fd[1]);
				run(token1, root);
				exit(0);
			}
			if (fork()==0) {
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				run(token2, root);
				exit(0);
			}
			close(fd[0]);
			close(fd[1]);
			wait(&status1);
			finish(WEXITSTATUS(status1), token1, prev);
			wait(&status2);
			finish(WEXITSTATUS(status2), token2, prev);
		}
		getcwd(temp, FILENAME_MAX);
		if (strcmp(temp, path) != 0)
			strcpy(prev, path);
	}
	
}