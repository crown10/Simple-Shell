#include <stdio.h>
#include "main.h"
/**
 * _read_command- reads and interpret command line
 * @cmd : cmd is the command input
 * @par : par is the array
 * Return: nothing
 */
void _read_command(char cmd[], char *par[])
{
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;

	for (;;)
	{
		int c = fgetc(stdin);
		line[count++] = (char) c;
		if (c == '\n')
			break;
	}
	if (count == 1)
		return;
	pch = strtok(line, "\n");
	while (pch != NULL)
	{
		array[i++] = strdup (pch);
		pch = strtok (NULL, "\n");
	}
	strcpy (cmd, array[0]);
	for (j = 0; j < i; j++)
	{
		par[j] = array[j];
	}
	par[i] = NULL;
}
/**
 * _type_prompt - provides writing place for input
 * Return: nothing
 */
void _type_prompt(void)
{
	static int first_time = 1;

	if (first_time)
	{
		const char* CLEAR_SCREEN_ANSI = "\x1b[1;1H\x1b[2J";
		write (STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		first_time = 0;
	}
	printf("#");
}
/**
 * main - interprets the command
 * Return: int
 */
int main(void)
{
	char cmd[100], command[100], *parameters[20];
	char *env[] = {(char *) "PATH=/bin", 0};

	while (1)
	{
		_type_prompt();
		_read_command (command, parameters);
		if (fork() != 0)
			wait (NULL);
		else
		{
			strcpy (cmd, "/bin/");
			strcat (cmd, command);
			execve (cmd, parameters, env);
		}
		if (strcmp (command, "exit") == 0)
			break;
	}
	return (0);
}
