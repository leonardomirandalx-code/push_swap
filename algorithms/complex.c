#include "push_swap.h"

int	bits_counter(size_t max)
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
	

void	complex_algorithm(t_data *data)
{

	size = stacksize(data->a) - 1;

