#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
#include <stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <dirent.h>
char pathname[1024][1024];
char ppath[1024];
int len = 0;

void ls(char *path, bool recurse_flag, char *per_path)
{
	DIR *dir;
  struct dirent *directory;
	struct stat buff;


// no -R flag, no path
	if(path == NULL && recurse_flag == false && per_path == "")
	{
		if(!(dir = opendir(".")))
		{
			printf("cannot access %s: No such file or directory\n", path);
			return;
		}
		// printf("dadad\n");
			dir == opendir(".");
			// chdir(dir);
			printf("%s\n", per_path);
			while((directory = readdir(dir)))
			{
				if(strncmp(directory->d_name, ".", 1) == 0)
				{
					continue;
				}
				printf("%s  ", directory->d_name);

				// if(stat(directory->d_name, &buff) >= 0 && S_ISDIR(buff.st_mode))
				// {
				// 	ls(directory->d_name, false);
				// }
			}
		printf("\n");
	 closedir(dir);
	}

	else
	{
		//have -R flag, no path
		if(path == NULL && recurse_flag == true && per_path == ".")
		{

			if(!(dir = opendir(".")))
			{
				printf("cannot access %s: No such file or directory\n", path);
				return;
			}
			else
			{
				// printf(".:\n");
				printf("\n");
				getcwd(ppath, 1024);
				printf("%s:\n", ppath);
				while((directory = readdir(dir)) != NULL)
				{
						lstat(directory->d_name, &buff);
						if(S_IFDIR &buff.st_mode)
						{
							if(strncmp(directory->d_name, ".", 1) == 0)
							{
								continue;
							}
							// recurse_flag == true;
								if (strcmp(".", directory->d_name) == 0 || strcmp("..", directory->d_name) == 0)
									continue;

								printf("%s ", directory->d_name);
								ls(directory->d_name, recurse_flag, per_path);

						}
						else
						{
							recurse_flag == false;
							if(strncmp(directory->d_name, ".", 1) == 0)
							{
								continue;
							}
							printf("%s  ", directory->d_name);
							// strcpy(pathname1[len], directory->d_name);
							// strcat(pathname1[len], " ");
							// ls(directory->d_name, recurse_flag, per_path);
						}
				}
				// printf("%s\n", pathname1[len]);
				printf("\n");
				chdir("..");
				closedir(dir);
			}
		}





  // No -R, path given
	if(path && recurse_flag == false && per_path)
	{
		if((dir=opendir(path)) == NULL)
		{
			printf("cannot access %s: No such file or directory\n", path);
			return;
		}
		while((directory = readdir(dir)) != NULL)
		{
			if(strncmp(directory->d_name, ".", 1) == 0)
			{
				continue;
			}

			if (strcmp(".", directory->d_name) == 0 || strcmp("..", directory->d_name) == 0)
				continue;

			printf("%s  ", directory->d_name);

		}
		printf("\n");

	 closedir(dir);
	}


//  -R flag with some path name
	if(path && recurse_flag == true && per_path)
	{
						// printf("%s\n", pathname[len]);
		if((dir=opendir(path)) == NULL)
		{
			printf("cannot access %s: No such file or directory\n", path);
			return;
		}
		chdir(path);


			printf("\n");
			// strcpy(pathname[len], per_path);
			// printf("%s\n", pathname[len]);
			getcwd(ppath, 1024);
			printf("%s:\n", ppath);
		while((directory = readdir(dir)) != NULL)
    {

        lstat(directory->d_name, &buff);

        if(S_IFDIR &buff.st_mode)
        {
					if(strncmp(directory->d_name, ".", 1) == 0)
						continue;
          if (strcmp(".", directory->d_name) == 0 || strcmp("..", directory->d_name) == 0)
            continue;
					// strcat(pathname[len], "/");
					// strcat(pathname[len], directory->d_name);
					// strcat(pathname[len], " ");
					// per_path = pathname[len];

					printf("%s", directory->d_name);
					// printf("%s", buff);

					ls(directory->d_name, recurse_flag, per_path);
						// printf("\n");
        }

        if(!(S_IFDIR &buff.st_mode))
				{
					recurse_flag = false;
					if(strncmp(directory->d_name, ".", 1) == 0)
					{
						continue;
					}
					// strcpy(pathname1[len], path);
									// printf("%s", pathname[len]);
					// strcat(pathname[len], path);

          printf("%s  ", directory->d_name);
					// printf("%s  ", pathname1[len]);
				}
    }
		printf("\n");
    chdir("..");
    closedir(dir);
	}
	// printf("%s\n", pathname[len]);

 }
 return;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{ // No -R flag and no path name

		ls(NULL, false, "");
	}

	else if(strcmp(argv[1], "-R") == 0)
	{
		if(argc == 2)
		{ // only -R flag
			// printf("dasdadadasda\n");
			ls(NULL, true, ".");
		}

		else
		{ // -R flag with some path name

			ls(argv[2], true, argv[2]);

		}
	}
	else
	{ // no -R flag but path name is given

			ls(argv[1], false, "");


  }
	return 0;
}
