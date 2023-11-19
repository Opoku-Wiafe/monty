#include "monty.h"
/**
 * openmyfile -  open the file in question
 * @fileName: the name of the file
 * Return: the directory the file itself
 */
FILE *openmyfile(char *fileName)
{
	FILE *myFile;

	myFile = fopen(fileName, "r");
	if (!myFile)
	{
		fprintf(stderr, "Error: Cannot open the file %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	return (myFile);
}

/**
 * numberlen -  count how many charachter in number
 * @num: number
 * Return: the number lentgh
 */
size_t numberlen(int num)
{
	int len = 0;

	if (!num)
		return (1);
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

/**
 * numb_verification -  verify if number for push is valid or not
 * @to_ken: string tokenizer
 * Return: return Nothing
 */
void numb_verification(char *to_ken)
{
	int i = 0;

	if (atoi(to_ken) < 0)
		i++;
	if ((isdigit(to_ken[i]) && strlen(to_ken) == numberlen(atoi(to_ken))) ||
		(to_ken[0] == '-' && isdigit(to_ken[1])))
		data.push_value = atoi(to_ken);
	else
	{
		fprintf(stderr, "L%d: usage: push integer\n", data.line_n);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
}

/**
 * free_stack_holder -  clear everything from stack.
 * @top: head of the list
 * Return: return nothing.
 */
void free_stack_holder(stack_t *top)
{
	stack_t *change, *nav;

	for (change = top; change; change = nav)
	{
		nav = change->next;
		free(change);
	}
	data.top = NULL;
	fclose(data.my_file);
}
