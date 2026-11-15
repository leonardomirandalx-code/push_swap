#include "libft.h"

void	ft_reverse_rotate(t_list **lst)
{
	t_list	*temp;

	if (!*lst || !(*lst)->next)
		return ;
	temp = *lst;
	while (temp->next->next)
		temp = temp->next;
	ft_lstadd_front(lst, temp->next);
	temp->next = NULL;
}

void	ft_rra(t_list **a)
{
	ft_reverse_rotate(a);
	ft_putendl_fd("rra", 1);
}

void	ft_rrb(t_list **b)
{
	ft_reverse_rotate(b);
	ft_putendl_fd("rrb", 1);
}

void	ft_rrr(t_list **a, t_list **b)
{
	ft_reverse_rotate(a);
	ft_reverse_rotate(b);
	ft_putendl_fd("rrr", 1);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*ta;
	t_list	*tb;

	a = NULL;
	b = NULL;
	ft_lstadd_back(&a, ft_lstnew("ab"));
	ft_lstadd_back(&a, ft_lstnew("bc"));
	ft_lstadd_back(&a, ft_lstnew("cd"));
	ft_lstadd_back(&a, ft_lstnew("de"));
	ft_lstadd_back(&a, ft_lstnew("ef"));
	ft_lstadd_back(&b, ft_lstnew("12"));
	ft_lstadd_back(&b, ft_lstnew("23"));
	ft_lstadd_back(&b, ft_lstnew("34"));
	ft_lstadd_back(&b, ft_lstnew("45"));
	ft_lstadd_back(&b, ft_lstnew("56"));
	ta = a;
	tb = b;
	printf("List a:\n");
	while (ta)
	{
		printf("%s\n", (char *)ta->content);
		ta = ta->next;
	}
	printf("List b:\n");
	while (tb)
	{
		printf("%s\n", (char *)tb->content);
		tb = tb->next;
	}
	printf("\nLets swap\n\n");
	ft_rrr(&a, &b);
	printf("\n");
	ta = a;
	tb = b;
	printf("List a:\n");
	while (ta)
	{
		printf("%s\n", (char *)ta->content);
		ta = ta->next;
	}
	printf("List b:\n");
	while (tb)
	{
		printf("%s\n", (char *)tb->content);
		tb = tb->next;
	}
	return (0);
}*/
/*
ft_rotate
0 - Retornar em caso de pilha vazia ou 1 elemento
1 - Apontar temp para o primeiro nó
2 - Percorrer com temp até apontar para a penúltima posição
3 - ft_lstadd_front colocando o ultimo nó (temp->next) no começo
4 - Apontar a penúltima (guardada em temp) para NULL
*/
