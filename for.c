#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LINESIZE 1024


void execmd(char **argv);
char *get_location(char *command);

extern char **environ;

int main(int ac, char **argv)
{
	char line[LINESIZE];
    char *buff = NULL, *input_copy = NULL;
    size_t length = 0;
    ssize_t input;
    const char *delim = " \n";
    int token_no = 0;
    char *token;
    int i;
    int exitstatus = 0;
 //   char *ace;   
   // ace = (argv[0], "exit");
    //do
    //{  
    while (1)
    {
	do
	{
    		    printf("Shell$ ");
//	} while (input != '\0');
        	    input = getline(&buff, &length, stdin);
//		    i = execmd(argv);
       		if (input == -1)
       		{
        	 //   printf("Exit %s", delim);
        	   // return (-1);
			free(buff);
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
        	}
		else
		{
			char *p = strchr(line, '\n');

        		if (p)
        		    *p = 0;
    	  		if(strcmp(line, "exit") == 0)
        			  break;
		 }		
     /*  else if (ace != 0)
//         else if (input == ace)
	 {
		for (i = 0; argv[i]; i++)
			free(argv[i]);
		free(argv);
		free(buff);
		exit(exitstatus);

        } 
	else 
	{
		return (0);
	} 
*/
        input_copy = malloc(sizeof(char) * input);
        if (input_copy == NULL)
	{
            perror("Error with input");
            return (-1);
        }
    
        strcpy(input_copy, buff);
        
	token = strtok(buff, delim);

        while (token != NULL)
	{
            token_no++;
            token = strtok(NULL, delim);
        }
        token_no++;

        argv = malloc(sizeof(char *) * token_no);
        
	token = strtok(input_copy, delim);

        for (i = 0; token != NULL; i++)
	{
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
   //      } while (input != 0);
        
       argv[i] = NULL;

        execmd(argv); 
   //	} while (i);
	  } while (input != '\0');
    free(input_copy);
    free(buff);

    return (0);

//} while (i);
} 
}

void execmd(char **argv)
{
	int i, status, exitstatus = 0;
	char *command = NULL;
	char *bin_path = NULL;
	char *buffer;

	pid_t pid;

	pid = fork();
	if (argv)
	{
		if (pid == -1)
		{
			perror("page");
			exit (1);
		}
		if (pid == 0)
		{
		command = argv[0];
		bin_path = get_location(command);

		if (execve(bin_path, argv, environ) == -1)
		{
			perror("Error:");
			for (i = 0; argv[i]; i++)
				free(argv[i]);
			free(argv);
			free(buffer);
			exit(0);
        	}
		}
		wait(&status);
		if (WIFEXITED(status))
		{
			exitstatus = WEXITSTATUS(status);
		}
		for (i = 0; argv[i]; i++)
			free(argv[i]);
		free(argv);
		free(buffer);
		return;
    		}
}


char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;

	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");

		while(path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);

			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		
		if (stat(command,&buffer) == 0)
		{
			return (command);
		}

		return (NULL);
	}
	
	return (NULL);
}

