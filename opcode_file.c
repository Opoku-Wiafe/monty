#include "monty.h"

/**
 * _push -  adds a new node at the beginning stack
 * @top: head of double list
 * @line_number: line number of opcode
 * Return: nothing
 */
void _push(stack_t **top, unsigned int line_number)
{
	stack_t *new, *last_data;
	int i = 0;

	(void)line_number;
	if (!top)
		return;
	new = malloc(sizeof(stack_t));
	if (!new)
	{
		fprintf(stderr, "Error: Malloc execution failed");
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	new->n = data.push_value;
	if (data.mode == 0 || !*top)
	{
		if (*top)
		{
			new->next = *top;
			(*top)->prev = new;
		}
		else
			new->next = NULL;
		new->prev = NULL;
		*top = new;
	}
	else if (data.mode == 1)
	{
		last_data = *top;
		for (i = 0; last_data; i++)
		{
			if (!last_data->next)
				break;
			last_data = last_data->next;
		}
		last_data->next = new;
		new->prev = last_data;
		new->next = NULL;
	}
}

/**
 * _pall -  prints all data of a dlistint_t list
 * @top: head of double stack
 * @line_number: line of opcode
 * Return: Nothing
 */
void _pall(stack_t **top, unsigned int line_number)
{
	stack_t *current = *top;
	int i = 0;

	(void)line_number;
	while (current != NULL)
	{
		fprintf(stdout, "%d\n", current->n);
		current = current->next;
		i++;
	}
	fflush(stdout);
}

/**
 * _pint -  prints the figure at the top of the stack
 * @top: head of double list stack
 * @line_number: line of opcode
 * Return: Nothing
 */
void _pint(stack_t **top, unsigned int line_number)
{
	if (!*top)
	{
		fprintf(stderr, "L%d: cannot pint, nothing is stack\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "%d\n", (*top)->n);
	fflush(stdout);
}

/**
 * _pop - removes the  element at the top of the stack
 * @top: head of double list stack
 * @line_number: line number of opcode
 * Return: Nothing
 */
void _pop(stack_t **top, unsigned int line_number)
{

	if (!*top)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	if ((*top)->next == NULL)
	{
		free(*top);
		*top = NULL;
	}
	else
	{
		*top = (*top)->next;
		free((*top)->prev);
		(*top)->prev = NULL;
	}
}

/**
 * _swap - swaps elements at the top of the stack.
 * @top: head of double list stack
 * @line_number: line number of opcode
 * Return: Nothing
 */
void _swap(stack_t **top, unsigned int line_number)
{
	stack_t *temp;

	if (!*top || (*top)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, the stack too short\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	temp = *top;
	temp->prev = temp->next;
	if ((*top)->next->next == NULL)
		temp->next = NULL;
	else
	{
		temp->next = temp->next->next;
		temp->next->prev = *top;
	}
	*top = temp->prev;
	(*top)->prev = NULL;
	(*top)->next = temp;
}

/**
 * _add - adds the top two elements of the stack.
 * @top: head of double list stack
 * @line_number: line num of opcode
 * Return: Nothing
 */
void _add(stack_t **top, unsigned int line_number)
{
	int i = 0;

	if (!*top || (*top)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add it, stack too short\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	i = (*top)->n;
	_pop(&data.top, data.line_n);
	(*top)->n += i;
}

/**
 * _sub - subtracts the top element 1st and 2nd
 * @top: head of double list stack
 * @line_number: line number of opcode
 * Return: Nothing
 */
void _sub(stack_t **top, unsigned int line_number)
{
	int i = 0;

	if (!*top || (*top)->next == NULL)
	{
		fprintf(stderr, "L%d: cannot subtract, limit reached\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	i = (*top)->n;
	_pop(&data.top, data.line_n);
	(*top)->n -= i;
}

/**
 * _mul - multiply the top elements
 * @top: head of double list stack
 * @line_number: line of opcode
 * Return: Nothing
 */
void _mul(stack_t **top, unsigned int line_number)
{
	int i = 0;

	if (!*top || (*top)->next == NULL)
	{
		fprintf(stderr, "L%d: can't multiply, stack too short\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	i = (*top)->n;
	_pop(&data.top, data.line_n);
	(*top)->n *= i;
}

/**
 * _div - divide the elements at the top of stack
 * @top: head of double list stack
 * @line_number: line of opcode
 * Return: Nothing
 */

void _div(stack_t **top, unsigned int line_number)
{
	int i = 0;

	if (!*top || (*top)->next == NULL)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	if ((*top)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero not allowed\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	i = (*top)->n;
	_pop(&data.top, data.line_n);
	(*top)->n /= i;
}


/**
 * _mod - check for mod of division of top elements 
 * @top: head of double list stack
 * @line_number: line of opcode
 * Return: Nothing
 */
void _mod(stack_t **top, unsigned int line_number)
{
	int i = 0;

	if (!*top || (*top)->next == NULL)
	{
		fprintf(stderr, "L%d:can't check mod, stack too short\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	if ((*top)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero not allowed\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	i = (*top)->n;
	_pop(&data.top, data.line_n);
	(*top)->n %= i;
}

/**
 * _pchar - prints the char at the top of the stack (ascii).
 * @top: head of double list stack
 * @line_number: line number of opcode
 * Return: Nothing
 */
void _pchar(stack_t **top, unsigned int line_number)
{
	if (!*top)
	{
		fprintf(stderr, "L%d:can't pchar, the stack empty\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	if ((*top)->n > 127 || (*top)->n < 0)
	{
		fprintf(stderr, "L%d: can't pchar, value exceed limit\n", line_number);
		free_stack_holder(data.top);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", (*top)->n);
}
