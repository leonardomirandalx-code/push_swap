/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisilva <tisilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 08:17:46 by tisilva           #+#    #+#             */
/*   Updated: 2026/11/27 08:47:19 by tisilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_disorder(float disorder)
{
	size_t	whole;
	size_t	decimal;

	disorder *= 100;
	whole = (size_t)disorder;
	decimal = (size_t)((disorder - whole) * 100);
	putnbr(whole);
	write(2, ".", 1);
	if (decimal < 10)
		write(2, "0", 1);
	putnbr(decimal);
	write(2, "%", 1);
}

static char	*get_algorithm(t_algorithm algorithm)
{
	if (algorithm == SIMPLE)
		return ("simple");
	if (algorithm == MEDIUM)
		return ("medium");
	if (algorithm == COMPLEX)
		return ("complex");
	return ("adaptive");
}

static size_t	get_total_ops(t_data *data)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (i < OP_COUNT)
	{
		total += data->ops[i];
		i++;
	}
	return (total);
}

static void	print_op(t_data *data, char *name, t_actions action)
{
	putstr("[bench] ");
	putstr(name);
	putstr(": ");
	putnbr(data->ops[action]);
	write(2, "\n", 1);
}

void	print_bench(t_data *data)
{
	if (!data)
		return ;
	putstr("[bench] disorder: ");
	put_disorder(data->disorder);
	write(2, "\n", 1);
	putstr("[bench] strategy: ");
	putstr(get_algorithm(data->algorithm));
	write(2, "\n", 1);
	putstr("[bench] total_ops: ");
	putnbr(get_total_ops(data));
	write(2, "\n", 1);
	print_op(data, "sa", SA);
	print_op(data, "sb", SB);
	print_op(data, "ss", SS);
	print_op(data, "pa", PA);
	print_op(data, "pb", PB);
	print_op(data, "ra", RA);
	print_op(data, "rb", RB);
	print_op(data, "rr", RR);
	print_op(data, "rra", RRA);
	print_op(data, "rrb", RRB);
	print_op(data, "rrr", RRR);
}
