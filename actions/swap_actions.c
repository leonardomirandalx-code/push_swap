#include "push_swap.h"

void	swap(t_stack **stk)
{
	t_stack	*temp;

	if (!*stk || !(*stk)->next)
		return ;
	temp = *stk;
	*stk = temp->next;
	temp->next = (*stk)->next;
	(*stk)->next = temp;
}

void	sa(t_stack **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

void	sb(t_stack **b)
{
	swap(b);
	write(1, "sb\n", 3);
}
/*
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
        sa(&head);
	while (head)
        {
                printf("%d\n", head->value);
                head = head->next;
        }
        return (0);
}*/

#include <stdio.h>

static void	print_stacks(t_stack *a, t_stack *b, char *msg)
{
	printf("--- %s ---\na: ", msg);
	while (a)
	{
		printf("%d ", a->value);
		a = a->next;
	}
	printf("\nb: ");
	while (b)
	{
		printf("%d ", b->value);
		b = b->next;
	}
	printf("\n\n");
}

int	main(void)
{
	t_stack	*a;
	t_stack	*b;
	int		n;

	a = NULL;
	b = NULL;
	n = 1;
	while (n <= 4)
	{
		ft_stackadd_bottom(&a, ft_stacknew(n));
		ft_stackadd_bottom(&b, ft_stacknew(n * 10));
		n++;
	}
	print_stacks(a, b, "inicio");
	sa(&a);
	print_stacks(a, b, "depois de sa");
	sb(&b);
	print_stacks(a, b, "depois de sb");
	ss(&a, &b);
	print_stacks(a, b, "depois de ss");
	return (0);
}
