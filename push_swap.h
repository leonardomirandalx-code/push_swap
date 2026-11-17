#ifndef PUSH_SWAP.H
# define PUSH_SWAP.H

#include <stdlib.h>

typedef struct	s_stack
{
	int	value;
	struct s_stack	*next;
}	t_stack;

typedef enum e_algorithm
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_algorithm;

typedef enum e_token_type
{
	INVALID,
	NUMBER,
	FLAG
}	t_token_type;

#endif
