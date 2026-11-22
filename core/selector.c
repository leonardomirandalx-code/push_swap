#include "push_swap.h"

void	select_algorithm(t_data *data)
{
	if (data->options.flag == SIMPLE)
		simple_algorithm(data);/*
	else if (data->options.flag == MEDIUM)
		medium_algorithm(data);
	else if (data->options.flag == COMPLEX)
		complex_algorithm(data);
	else if (data->options.flag == ADAPTIVE)
		adaptive_algorithm(data);*/
}

void	select_bench(t_data *data)
{
	if (data->options.bench)
		print_bench(data);
}
