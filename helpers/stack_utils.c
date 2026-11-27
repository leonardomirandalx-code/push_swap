/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisilva <tisilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 08:17:46 by tisilva           #+#    #+#             */
/*   Updated: 2026/11/27 08:38:41 by tisilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

unsigned int	stacksize(t_stack *stk)
{
	unsigned int	i;

	if (!stk)
		return (0);
	i = 1;
	while (stk->next)
	{
		i++;
		stk = stk->next;
	}
	return (i);
}

t_stack	*find_bottom(t_stack *stk)
{
	if (!stk)
		return (NULL);
	while (stk->next)
		stk = stk->next;
	return (stk);
}

void	add_bottom(t_stack **stk, t_stack *new)
{
	if (!stk || !new)
		return ;
	if (*stk == NULL)
	{
		*stk = new;
		return ;
	}
	find_bottom(*stk)->next = new;
}

t_stack	*new_stack(int value)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->next = NULL;
	new->index = 0;
	return (new);
}

void	add_top(t_stack **stk, t_stack *new)
{
	t_stack	*temp;

	if (!stk || !new)
		return ;
	temp = *stk;
	*stk = new;
	new->next = temp;
}
