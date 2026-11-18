#include "push_swap.h"

void	push(t_stack **src, t_stack **dest)
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
}

void	pushx(t_stack **a, t_stack **b, char name)
{
	if (name == 'a')
	{
		push(b, a);
		write(1, "pa\n", 3);
	}
	else
	{
		push(a, b);
		write(1, "pb\n", 3);
	}
}
