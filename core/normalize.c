#include "push_swap.h"
#include <stdio.h>

void	normalize(t_data *data)
{
	t_stack	*temp;
	t_stack	*actual;
	size_t	index;
	
	actual = data->a;
	while (actual)
	{
		index = 0;
		temp = data->a;
		while (temp)
		{
			if (actual->value > temp->value)
				index++;
			temp = temp->next;
		}
		actual->index = index;
		printf("%zu\n", actual->index);
		actual = actual->next;
	}
}

int	main(void)
{
	t_data	data;
	t_stack	*temp;

	data = (t_data){0};
	add_bottom(&data.a, new_stack(42));
	add_bottom(&data.a, new_stack(-7));
	add_bottom(&data.a, new_stack(1000));
	add_bottom(&data.a, new_stack(1001));
	add_bottom(&data.a, new_stack(1002));
	add_bottom(&data.a, new_stack(3));
	normalize(&data);
	temp = data.a;
	while (temp)
	{
		printf("value: %5d   index: %zu\n", temp->value, temp->index);
		temp = temp->next;
	}
	free_stack(&data.a);
	return (0);
}
