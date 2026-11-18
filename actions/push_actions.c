#include "push_swap.h"

void	push(t_stack **src, t_stack **dest)
{
	t_stack	*temp_src;
	t_stack	*temp_dest;

	if (!src)
		return ;
	temp_src = *src;
	if ((*src)->next)
		*src = (*src)->next;
	else
		(*src)->next = NULL;
	temp_dest = *dest;
	*dest = temp_src;
	(*dest)->next = temp_dest;
}

#include <stdio.h>

int	main(void)
{
	t_stack	*a;
	t_stack	*b;
	t_stack	*tmp;
	int		n;

	a = NULL;
	b = NULL;
	n = 1;
	while (n <= 3)
		add_bottom(&a, new_stack(n++));

	printf("inicio\na: ");
	tmp = a; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\nb: ");
	tmp = b; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\n\n");

	push(&a, &b);
	printf("push 1 (b estava vazia)\na: ");
	tmp = a; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\nb: ");
	tmp = b; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\n\n");

	push(&a, &b);
	printf("push 2\na: ");
	tmp = a; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\nb: ");
	tmp = b; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\n\n");

	push(&a, &b);
	printf("push 3 (a tinha 1 elemento)\na: ");
	tmp = a; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\nb: ");
	tmp = b; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\n\n");

	push(&a, &b);
	printf("push 4 (a vazia, nada deve mudar)\na: ");
	tmp = a; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\nb: ");
	tmp = b; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\n\n");

	push(&b, &a);
	printf("push de volta (b -> a)\na: ");
	tmp = a; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\nb: ");
	tmp = b; while (tmp) { printf("%d ", tmp->value); tmp = tmp->next; }
	printf("\n");
	return (0);
}
