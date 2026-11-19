#include "push_swap.h"

void	rrr(t_stack **a, t_stack **b)
{
	if (!a || !*a || !(*a)->next || !b || !*b || !(*b)->next)
		return ;
	reverse_rotate(a, 0);
	reverse_rotate(b, 0);
	write(1, "rrr\n", 4);
}

void	rr(t_stack **a, t_stack **b)
{
	if (!a || !*a || !(*a)->next || !b || !*b || !(*b)->next)
		return ;
	rotate(a, 0);
	rotate(b, 0);
	write(1, "rr\n", 3);
}

void	ss(t_stack **a, t_stack **b)
{
	if (!a || !*a || !(*a)->next || !b || !*b || !(*b)->next)
		return ;
	swap(a, 0);
	swap(b, 0);
	write(1, "ss\n", 3);
}
