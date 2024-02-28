#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * read_command - Read user input
 *
 * Return: string containing user input
 */

char *read_command(void)
{
	char buffer[1024];
	char *command;

	printf("($) ");

	if (fgets(buffer, sizeof(buffer), stdin) == NULL)
	{
		return (NULL); /* Handle end-of-file (Ctrl+D) */
	}

	/* Remove newline character */
	buffer[strcspn(buffer, "\n")] = '\0';

	/* Allocate memory for the command (excluding the null terminator) */
	command = malloc(strlen(buffer) + 1);

	if (command == NULL)
	{
		/* Handle memory allocation error */
		return (NULL);
	}

	/* Copy the command from buffer */
	strcpy(command, buffer);

	return (command);
}
