#include "push_swap.h"

void	free_stack(t_stack **stack)
{
	t_stack	*temp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
}

void	free_all(t_stack **a, t_stack **b)
{
	free_stack(a);
	free_stack(b);
}

void	free_words(char **words, int count)
{
	while (count > 0)
		free(words[--count]);
	free(words);
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
