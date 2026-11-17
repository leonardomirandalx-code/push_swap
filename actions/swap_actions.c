#include "push_swap.h"

void	swap(t_stack **stk)
{
	t_stack	*temp;

	if (!*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = temp->next;
	temp->next = *stk->next;
	*stk->next = temp;
}

#include <stdio.h>
int     main(void)
{
        t_stack *head;
        int     n;

        n = 0;
        head = NULL;
        while (n < 9)
        {
                ft_stackadd_bottom(&head, ft_stacknew(n));
                n++;
        }
        ft_stackadd_bottom(&head, ft_stacknew(-1));
        ft_stackadd_bottom(&head, ft_stacknew(-12));
        t_stack *tmp = head;
        while (head)
        {
                printf("%d\n", head->value);
                head = head->next;
        }
        printf("%f\n", ft_compute_disorder(tmp));
        return (0);
}
