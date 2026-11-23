#include "push_swap.h"

float	compute_disorder(t_stack *a)
{
	size_t	mistakes;
	size_t	total_pairs;
	t_stack	*temp;

	if (!a || !a->next)
		return (0);
	mistakes = 0;
	total_pairs = 0;
	while (a)
	{
		temp = a->next;
		while (temp)
		{
			if (a->value > temp->value)
				mistakes++;
			temp = temp->next;
			total_pairs++;
		}
		a = a->next;
	}
	return ((float)mistakes / total_pairs);
}