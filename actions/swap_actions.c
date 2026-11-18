#include "push_swap.h"

void	swap(t_stack **stk)
{
	t_stack	*temp;

	if (!stk || !*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = temp->next;
	temp->next = (*stk)->next;
	(*stk)->next = temp;
}

void	sx(t_stack **stk, char name)
{
	swap(stk);
	if (name == 'a')
		write(1, "sa\n", 3);
	else
		write(1, "sb\n", 3);
}
