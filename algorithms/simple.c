#include "push_swap.h"

static unsigned int	find_min(t_stack *a)
{
	int				min;
	unsigned int	p_min;
	unsigned int	position;

	min = a->value;
	p_min = 0;
	position = 0;
	while (a)
	{
		if (min > a->value)
		{
			min = a->value;
			p_min = position;
		}
		a = a->next;
		position++;
	}
	return (p_min);
}

void	simple_algorithm(t_data *data)
{
	unsigned int	p_min;

	while (stacksize(data->a) > 0 && !is_sorted(data->a))
	{
		p_min = find_min(data->a);
		if (p_min <= stacksize(data->a) / 2)
		{
			while (p_min > 0)
			{
				rotate(data, &data->a, 'a');
				p_min--;
			}
		}
		else
		{
			while (p_min < stacksize(data->a))
			{
				reverse_rotate(data, &data->a, 'a');
				p_min++;
			}
		}
		push(data, &data->a, &data->b, 'b');
	}
	while (stacksize(data->b) > 0)
		push(data, &data->b, &data->a, 'a');
}
