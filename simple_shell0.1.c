#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execlp(line, line, NULL) == -1)
			{
				perror("execlp");
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
