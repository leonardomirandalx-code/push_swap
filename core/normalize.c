/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisilva <tisilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 08:17:46 by tisilva           #+#    #+#             */
/*   Updated: 2026/11/27 08:54:50 by tisilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		actual = actual->next;
	}
}
