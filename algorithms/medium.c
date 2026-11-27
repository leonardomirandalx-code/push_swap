/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisilva <tisilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 08:17:46 by tisilva           #+#    #+#             */
/*   Updated: 2026/11/27 08:35:47 by tisilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static unsigned int	find_max(t_stack *stack)
{
	size_t			max;
	unsigned int	pos;
	unsigned int	max_pos;

	max = stack->index;
	pos = 0;
	max_pos = 0;
	while (stack)
	{
		if (stack->index > max)
		{
			max = stack->index;
			max_pos = pos;
		}
		stack = stack->next;
		pos++;
	}
	return (max_pos);
}

static void	push_chunk(t_data *data, size_t low, size_t high)
{
	unsigned int	count;

	count = stacksize(data->a);
	while (count > 0)
	{
		if (data->a->index >= low && data->a->index < high)
			push(data, &data->a, &data->b, 'b');
		else
			rotate(data, &data->a, 'a');
		count--;
	}
}

static void	rotate_max(t_data *data, unsigned int pos, unsigned int size)
{
	if (pos <= size / 2)
		while (pos > 0)
		{
			rotate(data, &data->b, 'b');
			pos--;
		}
	else
		while (pos < size)
		{
			reverse_rotate(data, &data->b, 'b');
			pos++;
		}
}

static void	restore_chunk(t_data *data)
{
	unsigned int	size;
	unsigned int	pos;

	while (data->b)
	{
		size = stacksize(data->b);
		pos = find_max(data->b);
		rotate_max(data, pos, size);
		push(data, &data->b, &data->a, 'a');
	}
}

void	medium_algorithm(t_data *data)
{
	size_t	high;
	size_t	low;
	size_t	chunk;

	if (!data || !data->a || is_sorted(data->a))
		return ;
	high = stacksize(data->a);
	chunk = 1;
	while (chunk <= (high - 1) / chunk)
		chunk++;
	chunk *= 2;
	while (high > 0)
	{
		low = 0;
		if (high > chunk)
			low = high - chunk;
		push_chunk(data, low, high);
		restore_chunk(data);
		high = low;
	}
}
