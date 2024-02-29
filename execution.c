#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * execute_command - create processes to execute command file
 * @command: string containing user input
 *
 * Return: Either failure or success
 */

int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *const *argvec = {NULL};
	extern char **environ;
	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];

	/* Check for built-in commands */
	if (strcmp(command, "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (strcmp(command, "env") == 0)
	{
		print_environment();
		return (EXIT_SUCCESS);
	}

	/* Get the PATH environment variable */
	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not found\n");
		return (EXIT_FAILURE);
	}

	/* Create a copy to avoid modifying the original PATH */
	path_copy = strdup(path);

	while ((dir = strtok(path_copy, ":")) != NULL)
	{
		/* Construct the full path */
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

		/* Check if file exists and is executable */
		if (access(full_path, X_OK) == 0)
		{
			/* Fork a child process */
			pid = fork();
			/* Handle fork error */

			if (pid == -1)
				return (EXIT_FAILURE);
			else if (pid == 0)
			{
				/* Execute the command using the full path */
				if (execve(full_path, argvec, environ) == -1)
				{
					/* Handle execve error */
					fprintf(stderr, "Error: %s: failed to execute\n", full_path);

				}
				break; /* Exit after successful execution */
				return (EXIT_SUCCESS);
			}
			else
			{
				/* Parent process */
				wait(&status);
				if (WIFEXITED(status))
					return (WEXITSTATUS(status));
				/* Handle abnormal child process termination */
				return (EXIT_FAILURE);
			}
		}

		path_copy = NULL; /* Reset strtok for next iteration */
		dir = strtok(NULL, ":"); /* Get next directory */
	}

	/* If no path found, report command not found */
	fprintf(stderr, "Error: %s: command not found\n", command);
	free(path_copy); /* Free the allocated memory */
	
	return (EXIT_FAILURE); /* Should never reach here */
}
