#include "push_swap.h"

static int	bits_counter(size_t max)
{
	int	counter;

	counter = 0;
	while (max)
	{
		max = max >> 1;
		counter++;
	}
	return (counter);
}

static int	get_bit(size_t index, int position)
{
	return ((index >> position) & 1);
}
	
void	complex_algorithm(t_data *data)
{
	int	size;
	int	rounds;
	int	current_bit;
	int	pos;

	size = stacksize(data->a);
	if (size < 2)
		return ;
	rounds = bits_counter(size - 1);
	current_bit = 0;
	while (current_bit < rounds)
	{
		pos = 0;
		while (pos < size)
		{
			if (get_bit(data->a->index, current_bit))
				rotate(data, &data->a, 'a');
			else
				push(data, &data->a, &data->b, 'b');
			pos++;
		}
		while (stacksize(data->b))
			push(data, &data->b, &data->a, 'a');
		current_bit++;
	}
}
