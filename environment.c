#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * print_environment - handling env built-in command and environment variables
 *
 * Return: void
 */

void print_environment(void)
{
	char **env;
	extern char **environ;

	/* Loop through environment variables and print them */
	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
