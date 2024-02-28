#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * main - Entry point
 * Description : Read command and handle errors
 *
 * Return: Exit either success or failure
 */

int main(void)
{
	int status;
	char *command;

	while (1)
	{
		command = read_command();

		if (command == NULL)
		{
			/* Handle end-of-file (Ctrl+D) */
			break;
		}

		status = execute_command(command);
		if (status == EXIT_FAILURE)
		{
			/* Handle errors */
			free(command); /* Free memory allocated for the command */
			continue;
		}

		free(command); /* Free memory allocated for the command */
	}

	/* Cleanup tasks */
	return (EXIT_SUCCESS);
}
