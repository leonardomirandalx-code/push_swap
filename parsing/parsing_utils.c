#include "push_swap.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (INVALID);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (INVALID);
		i++;
	}
	return (NUMBER);
}
int	is_flag(char *str)
{
	if (!ft_strcmp(str, "--simple"))
		return (SIMPLE);
	if (!ft_strcmp(str, "--medium"))
		return (MEDIUM);
	if (!ft_strcmp(str, "--complex"))
		return (COMPLEX);
	if (!ft_strcmp(str, "--adaptive"))
		return (ADAPTIVE);
	return (INVALID);
}

int	is_dup(t_stack *stack)
{
	t_stack	*current;
	t_stack	*check;

	current = stack;
	while (current)
	{
		check = current->next;
		while (check)
		{
			if (current->value == check->value)
				return (1);
			check = check->next;
		}
		current = current->next;
	}
	return (0);
}

int	is_sorted(t_stack *a)
{
	if (!a)
		return (1);
	while (a->next)
        {
		if (a->value > a->next->value)
			return (0);
		a = a->next;
	}
	return (1);
}
