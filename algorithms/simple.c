#include "push_swap.h"

void	bubble_sort(t_stack **a, t_stack **b)
{
	int	flag;
	t_stack *temp_a;
	t_stack	*temp_b;
	int	p;

	flag = 1;
	while (flag == 1)
	{
		temp_a = *a;
		p = 0;
		while (temp_a)
		{
			if (temp_a->value < temp_a->next->value)
			{
				while (p >= 0)
				{
					ra
