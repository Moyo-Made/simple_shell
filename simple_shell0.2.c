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
	char *tokens[BUFFER_SIZE / 2 + 1];
	pid_t pid;
	int status;

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

		char *token = strtok(line, " ");
		int i = 0;
		while (token != NULL)
		{
			tokens[i++] = token;
			token = strtok(NULL, " ");
		}
		tokens[i] = NULL;

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execvp(tokens[0], tokens) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
