#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "wait.h"

#define BUFFER_SIZE 1024

/**
 * main - Entry point
 * Return: Always 0
*/
int main(void)
{
	char line[BUFFER_SIZE];
	pid_t pid;
	int status;
	char *path = getenv("PATH");

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(line, BUFFER_SIZE, stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		line[strlen(line)-1] = '\0';

		char *token = strtok(path, ":");
		while (token != NULL)
		{
			char cmd_path[BUFFER_SIZE];
			snprintf(cmd_path, BUFFER_SIZE, "%s/%s",token, line);
			if (access(cmd_path, X_OK) == 0)
			{
				pid = fork();
				if (pid < 0)
				{
					perror("fork");
					exit(EXIT_FAILURE);
				}
				else if (pid == 0)
				{
					if (execl(cmd_path, line, NULL)  == -1)
					{
						perror("execl");
						exit(EXIT_FAILURE);
					}
				}
				else
				{
					waitpid(pid, &status, 0);
				}
			}
			token = strtok(NULL, ":");
		}
	}
	return (0);
}
