#include "push_swap.h"

unsigned int	ft_stacksize(t_stack *stk)
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

t_stack	*ft_stacklast(t_stack *stk)
{
	if (!stk)
		return (NULL);
	while (stk->next)
		stk = stk->next;
	return (stk);
}

void	ft_stackadd_bottom(t_stack **stk, t_stack *new)
{
	if (!stk || !new)
		return ;
	if (*stk == NULL)
	{
		*stk = new;
		return ;
	}
	ft_stacklast(*stk)->next = new;
}

t_stack	*ft_stacknew(int value)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_stackadd_top(t_stack **stk, t_stack *new)
{
	t_stack	*temp;

	if (!stk || !new)
		return ;
	temp = *stk;
	*stk = new;
	new->next = temp;
}
