#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
#include <stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <dirent.h>

// int len = 0;
void ls(char *path, bool recurse_flag)
{
	DIR *dir;
  struct dirent *directory;
	struct stat buff;

// no -R flag, no path
	if(path == NULL && recurse_flag == false)
	{
		// printf("dadad\n");
		// dir == opendir(".");
		if(!(dir = opendir(".")))
		{
			printf("cannot access %s: No such file or directory\n", path);
			return;
		}
		else
		{
			while((directory = readdir(dir)) != NULL)
			{
				if(strncmp(directory->d_name, ".", 1) == 0)
				{
					continue;
				}
				printf("%s  ", directory->d_name);

				if(stat(directory->d_name, &buff) >= 0 && S_ISDIR(buff.st_mode))
				{
					ls(directory->d_name, false);
				}
			}
		printf("\n");
    }
	 closedir(dir);
	}

	else
	{
		//have -R flag, no path
		if(path == NULL && recurse_flag == true)
		{
			// dir == ".";
			if(!(dir = opendir(".")))
			{
				printf("cannot access %s: No such file or directory\n", path);
				return;
			}
			else
			{
				printf(".:\n");
				while((directory = readdir(dir)) != NULL)
				{
						lstat(directory->d_name, &buff);
						if(S_IFDIR &buff.st_mode)
						{
							// recurse_flag == true;
								if (strcmp(".", directory->d_name) == 0 || strcmp("..", directory->d_name) == 0)
									continue;

								printf("%s/\n", directory->d_name);
								ls(directory->d_name, true);

						}
						else
						{
							recurse_flag == false;
							printf("%s\t", directory->d_name);
						}
				}
				printf("\n");
				chdir("..");
				closedir(dir);
			}
		}

		// dir = opendir(path);

  	else if(!(dir = opendir(path)))
		{
			printf("cannot access %s: No such file or directory\n", path);
			return;
		}
		// printf("%s\n", path);

		else if(path == NULL && recurse_flag == true)
		{
			// dir = opendir(path[2]);
    	// printf("asdasd\n");

			chdir(path);
    	while((directory = readdir(dir)) != NULL)
    	{
        	lstat(directory->d_name, &buff);
        	if(S_IFDIR &buff.st_mode)
        	{
						// recurse_flag == true;
            	if (strcmp(".", directory->d_name) == 0 || strcmp("..", directory->d_name) == 0)
              continue;

            	printf("%s/\n", directory->d_name);
							ls(directory->d_name, true);

        	}
        	else
					{
						recurse_flag == false;
          	printf("%s\t", directory->d_name);
					}
    	}
			printf("\n");
    	chdir("..");
    	closedir(dir);
		}


  //No -R flag, have path
	else if(path[1] && recurse_flag == false)
	{
		while((directory = readdir(dir)) != NULL)
		{
			if(strncmp(directory->d_name, ".", 1) == 0)
			{
				continue;
			}
			// strcpy(filename[len++], directory->d_name);
			printf("%s  ", directory->d_name);

			if(stat(directory->d_name, &buff) >= 0 && S_ISDIR(buff.st_mode))
			{
				ls(directory->d_name, false);
			}
		}
		printf("\n");

	 closedir(dir);
	}


//  -R flag with some path name
	else if(path[2] && recurse_flag == true)
	{
		// dir = opendir(path[2]);
    // printf("asdasd\n");
		chdir(path);
    while((directory = readdir(dir)) != NULL)
    {
        lstat(directory->d_name, &buff);
        if(S_IFDIR &buff.st_mode)
        {
					// recurse_flag == true;
            if (strcmp(".", directory->d_name) == 0 || strcmp("..", directory->d_name) == 0)
              continue;

            printf("%s/\n", directory->d_name);
						ls(directory->d_name, true);

        }
        else
				{
					recurse_flag == false;
          printf("%s\t", directory->d_name);
				}
    }
		printf("\n");
    chdir("..");
    closedir(dir);
	}

 }
 return;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{ // No -R flag and no path name
		// printf("in\n");
		ls(NULL, false);
	}

	else if(strcmp(argv[1], "-R") == 0)
	{
		if(argc == 2)
		{ // only -R flag
			ls(NULL, true);
		}

		else
		{ // -R flag with some path name
     	// printf("1122");
			ls(argv[2], true);

		}
	}
	else
	{ // no -R flag but path name is given
      // printf("sda\n");
			ls(argv[1], false);


  }
	return 0;
}
