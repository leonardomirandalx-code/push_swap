/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisilva <tisilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 08:17:46 by tisilva           #+#    #+#             */
/*   Updated: 2026/11/27 08:34:51 by tisilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rrr(t_data *data)
{
	if (!data || ((!data->a || !data->a->next)
			&& (!data->b || !data->b->next)))
		return ;
	reverse_rotate(data, &data->a, 0);
	reverse_rotate(data, &data->b, 0);
	data->ops[RRR]++;
	write(1, "rrr\n", 4);
}

void	rr(t_data *data)
{
	if (!data || ((!data->a || !data->a->next)
			&& (!data->b || !data->b->next)))
		return ;
	rotate(data, &data->a, 0);
	rotate(data, &data->b, 0);
	data->ops[RR]++;
	write(1, "rr\n", 3);
}

void	ss(t_data *data)
{
	if (!data || ((!data->a || !data->a->next)
			&& (!data->b || !data->b->next)))
		return ;
	swap(data, &data->a, 0);
	swap(data, &data->b, 0);
	data->ops[SS]++;
	write(1, "ss\n", 3);
}

