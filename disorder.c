#include "push_swap.h"

double	compute_disorder(t_stack *a)
{
	size_t	mistakes;
	size_t	total_pairs;
	t_stack	*temp;

	if (!a || !a->next)
		return (0);
	mistakes = 0;
	total_pairs = 0;
	while (a)
	{
		temp = a->next;
		while (temp)
		{
			if (a->value > temp->value)
				mistakes++;
			temp = temp->next;
			total_pairs++;
		}
		a = a->next;
	}
	return ((double)mistakes / total_pairs);
}
/*
#include <stdio.h>
int	main(void)
{
	t_stack	*head;
	int	n;

	n = 0;
	head = NULL;
	while (n < 9)
	{
		ft_stackadd_bottom(&head, ft_stacknew(n));
		n++;
	}
	ft_stackadd_bottom(&head, ft_stacknew(-1));
	ft_stackadd_bottom(&head, ft_stacknew(-12));
	t_stack	*tmp = head;
	while (head)
        {
                printf("%d\n", head->value);
                head = head->next;
        }
	printf("%f\n", ft_compute_disorder(tmp));
	return (0);
}*/
