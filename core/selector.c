#include "push_swap.h"

void	select_algorithm(t_data *data)
{
	if (data->options.flag == ADAPTIVE || data->options.flag == NONE)
	{
		if (data->disorder < 0.2)
			simple_algorithm(data);
		else if (data->disorder < 0.5)
			medium_algorithm(data);
		else
			complex_algorithm(data);
	}
	else if (data->options.flag == SIMPLE)
		simple_algorithm(data);
	else if (data->options.flag == MEDIUM)
		medium_algorithm(data);
	else if (data->options.flag == COMPLEX)
		complex_algorithm(data);
}

void	select_bench(t_data *data)
{
	if (data->options.bench)
		print_bench(data);
}
