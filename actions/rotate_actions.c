#include "push_swap.h"

void	reverse_rotate(t_stack **stk)
{
	t_stack	*temp;

	if (!stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	while (temp->next->next)
		temp = temp->next;
	add_top(stk, temp->next);
	temp->next = NULL;
}

void	rrx(t_stack **stk, char name)
{
	reverse_rotate(stk);
	if (name == 'a')
		write(1, "rra\n", 4);
	else
		write(1, "rrb\n", 4);
}

void	rotate(t_stack **stk)
{
	t_stack	*temp;

	if (!stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = (*stk)->next;
	temp->next = NULL;
	add_bottom(stk, temp);
}

void	rx(t_stack **stk, char name)
{
	rotate(stk);
	if (name == 'a')
		write(1, "ra\n", 3);
	else
		write(1, "rb\n", 3);
}
