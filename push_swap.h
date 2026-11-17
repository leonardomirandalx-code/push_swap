#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}	t_stack;

typedef enum e_algorithm
{
	NONE,
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_algorithm;

typedef enum e_type
{
	INVALID,
	NUMBER,
	FLAG
}	t_type;

typedef struct s_options
{
	t_algorithm	flag;
	int			bench;
}	t_options;

#endif