
#include "push_swap.h"

void	push(t_data *data, t_stack **src, t_stack **dest, char name)
{
	t_stack	*temp_src;
	t_stack	*temp_dest;

	if (!data || !src || !*src || !dest)
		return ;
	temp_src = *src;
	*src = (*src)->next;
	temp_dest = *dest;
	*dest = temp_src;
	(*dest)->next = temp_dest;
	if (name == 'a')
	{
		data->ops[PA]++;
		write(1, "pa\n", 3);
	}
	else if (name == 'b')
	{
		data->ops[PB]++;
		write(1, "pb\n", 3);
	}
}

void	reverse_rotate(t_data *data, t_stack **stk, char name)
{
	t_stack	*temp;

	if (!data || !stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	while (temp->next->next)
		temp = temp->next;
	add_top(stk, temp->next);
	temp->next = NULL;
	if (name == 'a')
	{
		data->ops[RRA]++;
		write(1, "rra\n", 4);
	}
	else if (name == 'b')
	{
		data->ops[RRB]++;
		write(1, "rrb\n", 4);
	}
}

void	rotate(t_data *data, t_stack **stk, char name)
{
	t_stack	*temp;

	if (!data || !stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = (*stk)->next;
	temp->next = NULL;
	add_bottom(stk, temp);
	if (name == 'a')
	{
		data->ops[RA]++;
		write(1, "ra\n", 3);
	}
	else if (name == 'b')
	{
		data->ops[RB]++;
		write(1, "rb\n", 3);
	}
}

void	swap(t_data *data, t_stack **stk, char name)
{
	t_stack	*temp;

	if (!data || !stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = temp->next;
	temp->next = (*stk)->next;
	(*stk)->next = temp;
	if (name == 'a')
	{
		data->ops[SA]++;
		write(1, "sa\n", 3);
	}
	else if (name == 'b')
	{
		data->ops[SB]++;
		write(1, "sb\n", 3);
	}
}
