#include <stdio.h>
#include "push_swap.h"

unsigned int	find_min(t_stack *a)
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

void	simple_sort(t_data *data)
{
	unsigned int	p_min;

	while (stacksize(data->a) > 0)
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

int	main(void)
{
	t_stack *temp_a;
	t_stack	*temp_b;
	t_data	data;

	data = (t_data){0};
	add_bottom(&data.a, new_stack(-9));
	add_bottom(&data.a, new_stack(-4));
	add_bottom(&data.a, new_stack(7));
	add_bottom(&data.a, new_stack(3));
	add_bottom(&data.a, new_stack(4));
	add_bottom(&data.a, new_stack(-8));
	add_bottom(&data.a, new_stack(6));
	data.b = NULL;
	temp_a = data.a;
	temp_b = data.b;
	printf("Stack a: \n");
	while (temp_a)
	{
		printf("%d\n", temp_a->value);
		temp_a = temp_a->next;
	}
	printf("\nStack b: \n");
	while (temp_b)
        {
                printf("%d\n", temp_b->value);
                temp_b = temp_b->next;
        }
	printf("\nThe disorder level is %f\n\n", compute_disorder(data.a));
	simple_sort(&data);
	printf("\n");
	temp_a = data.a;
	printf("Stack a: \n");
	while (temp_a)
        {
                printf("%d\n", temp_a->value);
                temp_a = temp_a->next;
        }
	temp_b = data.b;
	printf("\nStack b: \n");
	while (temp_b)
        {
                printf("%d\n", temp_b->value);
                temp_b = temp_b->next;
        }
	printf("\nThe disorder level is %f\n\n", compute_disorder(data.a));
}
