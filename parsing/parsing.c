#include "push_swap.h"

static int	check_stack(char *token, t_stack **stack_a)
{
	int		number;
	t_stack	*new;

	if (a_to_i(token, &number))
		return (1);
	new = new_stack(number);
	if (!new)
		return (1);
	add_bottom(stack_a, new);
	return (0);
}

static int	check_flags(char *token, t_options *op)
{
	t_algorithm	method;

	if (!ft_strcmp(token, "--bench"))
	{
		if (op->bench)
			return (1);
		op->bench = 1;
		return (0);
	}
	method = is_flag(token);
	if (method == NONE)
		return (1);
	if (op->flag != NONE)
		return (1);
	op->flag = method;
	return (0);
}

int	validation(char **tokens, t_options *op, t_stack **stack_a)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_number(tokens[i]) == NUMBER)
		{
			if (check_stack(tokens[i], stack_a))
				return (1);
		}
		else if (check_flags(tokens[i], op))
			return (1);
		i++;
	}
	return (is_dup(*stack_a));
}

int	parse_args(int argc, char **argv, t_options *options,
		t_stack **stack_a)
{
	char	**splits;
	int		i;
	int		count;

	i = 1;
	while (i < argc)
	{
		splits = split(argv[i]);
		if (!split)
			return (1);
		count = count_words(argv[i]);
		if (count == 0 || validation(splits, options, stack_a))
		{
			free_words(splits, count);
			return (1);
		}
		free_words(splits, count);
		i++;
	}
	return (0);
}