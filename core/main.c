#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (argc < 2)
		return (0);
	if (parse_args(argc, argv, &data.options, &data.a))
	{
		free_stack(&data.a);
		write(2, "Error\n", 6);
		return (1);
	}
	data.disorder = compute_disorder(data.a);
	select_algorithm(&data);
	select_bench(&data);
	free_stack(&data.a);
	free_stack(&data.b);
	return (0);
}