#include "push_swap.h"

void	validation(char **tokens, t_options op, t_algorithm method)
{
	int i;
	i = 0;
		while (tokens[i])
		{
			if (is_number(tokens[i]) == NUMBER)
				h_atoi(tokens[i], );
			else if (!ft_strcmp(tokens[i], "--bench"))
				op.bench = 1;
			else if ((method = is_flag(tokens[i])) != NONE)
				op.flag = method;
			else
			{
				free_words(tokens, i + 1);
				return (1);
			}
			i++;
		}
		free_words(tokens, i);
}

int	parse_args(int argc, char **argv, t_options *options)
{
	char		**split;
	t_algorithm	method;
	t_options	op;
	int			i;

	i = 1;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			return (1);
		validation(split, op, method);
		i++;
	}
	return (0);
}
