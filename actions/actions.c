#include "push_swap.h"

void	push(t_stack **src, t_stack **dest, char name)
{
	t_stack	*temp_src;
	t_stack	*temp_dest;

	if (!src || !*src || !dest)
		return ;
	temp_src = *src;
	*src = (*src)->next;
	temp_dest = *dest;
	*dest = temp_src;
	(*dest)->next = temp_dest;
	if (name == 'a')
		write(1, "pa\n", 3);
	else
		write(1, "pb\n", 3);
}

void	reverse_rotate(t_stack **stk, char name)
{
	t_stack	*temp;

	if (!stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	while (temp->next->next)
		temp = temp->next;
	add_top(stk, temp->next);
	temp->next = NULL;
	if (name == 'a')
		write(1, "rra\n", 4);
	else
		write(1, "rrb\n", 4);
}

void	rotate(t_stack **stk, char name)
{
	t_stack	*temp;

	if (!stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = (*stk)->next;
	temp->next = NULL;
	add_bottom(stk, temp);
	if (name == 'a')
		write(1, "ra\n", 3);
	else
		write(1, "rb\n", 3);
}

void	swap(t_stack **stk, char name)
{
	t_stack	*temp;

	if (!stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = temp->next;
	temp->next = (*stk)->next;
	(*stk)->next = temp;
	if (name == 'a')
		write(1, "sa\n", 3);
	else
		write(1, "sb\n", 3);
}
