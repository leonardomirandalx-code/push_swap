#include "libft.h"

void	ft_rotate(t_list **lst)
{
	t_list	*temp;

	if (!*lst || !(*lst)->next)
		return ;
	temp = *lst;
	*lst = (*lst)->next;
	temp->next = NULL;
	ft_lstadd_back(lst, temp);
}

void	ft_ra(t_list **a)
{
	ft_rotate(a);
	ft_putendl_fd("ra", 1);
}

void	ft_rb(t_list **b)
{
	ft_rotate(b);
	ft_putendl_fd("rb", 1);
}

void	ft_rr(t_list **a, t_list **b)
{
	ft_rotate(a);
	ft_rotate(b);
	ft_putendl_fd("rr", 1);
}

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
	printf("\nLets swap:\n\n");
	ft_rr(&a, &b);
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
}
/*
ft_rotate
0 - Retornar em caso de pilha vazia ou 1 elemento
1 - Guardar o primeiro no numa temporaria
2 - Apontar head para o segundo no
3 - Next do no guardado em temp a NULL
4 - ft_lstadd_back coloca o no guardado em temp no final
*/
