#include "monty.h"

/**
 * evoke - execute opcode 
 * Return: Nothing
 */
void evoke(void)
{
	instruction_t ins[] = {
		{"push", _push},
		{"pall", _pall},
		{"queue", _mode},
		{"stack", _mode},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},
		{"sub", _sub},
		{"div", _div},
		{"mul", _mul},
		{"mod", _mod},
		{"pchar", _pchar},
		{"pstr", _pstr},
		{NULL, NULL},
	};
	int i = 0;

	for (i = 0; ins[i].opcode; i++)
	{
		if (strcmp(data.opcode, ins[i].opcode) == 0)
		{
			ins[i].f(&data.top, data.line_n);
			break;
		}
	}
	if (!ins[i].opcode)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n",
				data.line_n, data.opcode);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
}
/**
 * remove_empty_spaces - remove spaces
 * @str: string of char passed
 * Return: cleaned string
 */
char *remove_empty_spaces(char *str)
{
	while (*str)
	{
		if (*str == ' ')
			str++;
		else
			break;
	}
	return (str);
}

/**
 * main -  count the exact number characters passed
 * @argc: length of the data
 * @argv: array of char passed.
 * Return: return the length of data passed
 */
int main(int argc, char **argv)
{
	char charac[100], *to_ken;
	int i = 0;

	data.mode = 0;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	data.my_file = openmyfile(argv[1]);

	for (; fgets(charac, sizeof(charac), data.my_file) != NULL; data.line_n++)
	{
		if (strlen(remove_empty_spaces(charac)) < 3 || remove_empty_spaces(charac)[0] == '#')
			continue;

		to_ken = strtok(charac, " \n");
		for (i = 0; to_ken != NULL && i < 2; i++)
		{
			if (i == 0)
				data.opcode = to_ken;

			if (strcmp(data.opcode, "push") != 0)
				break;

			if (i == 1)
				numb_verification(to_ken);

			to_ken = strtok(NULL, " \n");
		}

		if (strcmp(data.opcode, "push") == 0 && i == 1)
		{
			fprintf(stderr, "L%d: usage: push integer\n", data.line_n);
			free_stack_holder(data.top);
			exit(EXIT_FAILURE);
		}

		evoke();
	}
	free_stack_holder(data.top);
	exit(EXIT_SUCCESS);
}
