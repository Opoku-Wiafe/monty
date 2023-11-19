#include "monty.h"

/**
 * _pstr - prints the string of the top elements
 * @top: head of double list stack
 * @line_number: line of opcode
 * Return: Nothing
 */
void _pstr(stack_t **top, unsigned int line_number)
{
	stack_t *current = *top;
	int i;
	(void)line_number;

	for (i = 0; current && current->n != 0 &&
				!(current->n > 127 || current->n < 0);
		 i++)
	{
		fprintf(stdout, "%c", current->n);
		current = current->next;
	}
	fprintf(stdout, "\n");
}

/**
 * _nop - sorry message.
 * @top: head of double list stack
 * @line_number: line number of opcode
 * Return: Nothing to return
 */
void _nop(stack_t **top, unsigned int line_number)
{
	(void)top;
	(void)line_number;
}

/**
 * _mode -  switch from the mode (queue/stack)
 * @top: head of double list traversed
 * @line_number: line number of opcode
 * Return: Nothing
 */
void _mode(stack_t **top, unsigned int line_number)
{
	(void)top;
	(void)line_number;

	if (strcmp(data.opcode, "stack") == 0)
		data.mode = 0;
	else if (strcmp(data.opcode, "queue") == 0)
		data.mode = 1;
}
