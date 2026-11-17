#include "push_swap.h"

void	reverse_rotate(t_stack **stk)
{
	t_stack	*temp;

	if (!*stk || !(*stk)->next)
		return ;
	temp = *stk;
	while (temp->next->next)
		temp = temp->next;
	ft_stackadd_top(stk, temp->next);
	temp->next = NULL;
}

void	rra(t_stack **a)
{
	reverse_rotate(a);
	ft_putendl_fd("rra", 1);
}

void	rrb(t_stack **b)
{
	reverse_rotate(b);
	ft_putendl_fd("rrb", 1);
}
void	rotate(t_stack **stk)
{
	t_stack	*temp;

	if (!*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = (*stk)->next;
	temp->next = NULL;
	ft_stackadd_bottom(stk, temp);
}

void	ra(t_stack **a)
{
	rotate(a);
	ft_putendl_fd("ra", 1);
}

void	rb(t_stack **b)
{
	rotate(b);
	ft_putendl_fd("rb", 1);
}
