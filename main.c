#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*temp;
	t_options	options;

	stack_a = NULL;
	options.flag = ADAPTIVE;
	options.bench = 0;
	if (argc < 2)
		return (0);
	if (parse_args(argc, argv, &options, &stack_a))
	{
		free_stack(&stack_a);
		write(2, "Error\n", 6);
		return (1);
	}
	temp = stack_a;
	while (temp)
	{
		printf("%d\n", temp->value);
		temp = temp->next;
	}
	printf("Algorithm: %d\n", options.flag);
	printf("Bench: %d\n", options.bench);
	free_stack(&stack_a);
	return (0);
}