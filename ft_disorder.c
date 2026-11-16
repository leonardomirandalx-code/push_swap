#include "libft/libft.h"
#include <stdio.h>

typedef struct	s_stack
{
	int	value;
	struct s_stack	*next;
}	t_stack;

unsigned int	ft_lstsize_p(t_stack *lst)
{
	unsigned int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_stack	*ft_lstlast_p(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst-> next;
	return (lst);
}

void	ft_lstadd_back_p(t_stack **lst, t_stack *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ft_lstlast_p(*lst)->next = new;
}

t_stack	*ft_lstnew_p(int content)
{
	t_stack	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->value = content;
	new->next = NULL;
	return (new);
}

double	ft_compute_disorder(t_stack *a)
{
	size_t	mistakes;
	size_t	total_pairs;
	t_stack	*temp;

	if (!a->next)
		return (1);
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
	return ((double)mistakes/total_pairs);
}


// double	ft_compute_disorder(t_stack *stack)
// {
// 	t_stack	*i;
// 	t_stack	*j;
// 	size_t		mistakes;
// 	size_t		total;

// 	if (!stack || ft_lstsize_p(stack) < 2)
// 		return (0.0);
// 	mistakes = 0;
// 	total = (ft_lstsize_p(stack) * (ft_lstsize_p(stack) - 1) / 2);
// 	i = stack;
// 	while (i)
// 	{
// 		j = i->next;
// 		while (j)
// 		{
// 			if (i->value > j->value)
// 				mistakes++;
// 			j = j->next;
// 		}
// 		i = i->next;
// 	}
// 	printf("mistakes = %zu\n", mistakes);
//  	printf("total_pairs = %zu\n", total);
// 	return ((double)mistakes / total);
// }

int	main(void)
{
	t_stack	*head;
	int	n;

	n = 0;
	head = NULL;
	while (n < 20)
	{
		ft_lstadd_back_p(&head, ft_lstnew_p(n));
		n++;
	}
	ft_lstadd_back_p(&head, ft_lstnew_p(-1));
	t_stack	*tmp = head;
	while (head)
        {
                printf("%d\n", head->value);
                head = head->next;
        }
	printf("%f\n", ft_compute_disorder(tmp));
	return (0);
}
