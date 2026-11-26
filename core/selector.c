#include "push_swap.h"

void	select_algorithm(t_data *data)
{
	if (data->options.flag == ADAPTIVE
		|| data->options.flag == NONE)
	{
		if (data->disorder < 0.2)
			data->algorithm = SIMPLE;
		else if (data->disorder < 0.5)
			data->algorithm = MEDIUM;
		else
			data->algorithm = COMPLEX;
	}
	else
		data->algorithm = data->options.flag;
	if (data->algorithm == SIMPLE)
		simple_algorithm(data);
	else if (data->algorithm == MEDIUM)
		medium_algorithm(data);
	else if (data->algorithm == COMPLEX)
		complex_algorithm(data);
}

void	select_bench(t_data *data)
{
	if (data->options.bench)
		print_bench(data);
}
