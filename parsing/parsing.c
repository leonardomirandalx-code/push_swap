#include "push_swap.h"

int	validation(char **tokens, t_options *op, t_stack **stack_a)
{
	int			i;
	int			number;
	t_stack		*new;
	t_algorithm	method;

	i = 0;
	while (tokens[i])
	{
		if (is_number(tokens[i]) == NUMBER)
		{
			if (h_atoi(tokens[i], &number))
				return (1);
			new = new_stack(number);
			if (!new)
				return (1);
			add_bottom(stack_a, new);
		}
		else if (!ft_strcmp(tokens[i], "--bench"))
			op->bench = 1;
		else if ((method = is_flag(tokens[i])) != NONE)
			op->flag = method;
		else
			return (1);
		i++;
	}
	if (is_dup(*stack_a))
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_options *options,
		t_stack **stack_a)
{
	char	**split;
	int		i;
	int		count;

	i = 1;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			return (1);
		count = count_words(argv[i], ' ');
		if (count == 0 || validation(split, options, stack_a))
		{
			free_words(split, count);
			return (1);
		}
		free_words(split, count);
		i++;
	}
	return (0);
}