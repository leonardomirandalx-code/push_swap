#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# define DEC "0123456789"

typedef struct s_stack
{
	size_t				index;
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

//estrutura bench
typedef enum e_actions
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	OP_COUNT
}	t_actions;

typedef struct	s_data
{
	t_stack	*a;
	t_stack	*b;
	t_options	options;
	float	disorder;
	size_t	ops[OP_COUNT];
}	t_data;

char			**ft_split(char const *s);
void			free_words(char **words, int count);
int				count_words(char const *s);

int				h_atoi(const char *str, int *number);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
int				ft_strcmp(char *s1, char *s2);

int				is_number(char *str);
int				is_flag(char *str);
int				is_dup(t_stack *stack);
int				parse_args(int argc, char **argv, t_options *options,
								 t_stack **stack_a);
int				validation(char **tokens, t_options *op, t_stack **stack_a);

unsigned int	stacksize(t_stack *stk);
t_stack			*find_bottom(t_stack *stk);
void			add_bottom(t_stack **stk, t_stack *new);
void			add_top(t_stack **stk, t_stack *new);
t_stack			*new_stack(int value);
void			free_stack(t_stack **stack);
void			free_all(t_stack **a, t_stack **b);
int				is_sorted(t_stack *a);

float			compute_disorder(t_stack *a);
void			swap(t_data *data, t_stack **stk, char name);
void			ss(t_data *data);
void			rotate(t_data *data, t_stack **stk, char name);
void			rr(t_data *data);
void			reverse_rotate(t_data *data, t_stack **stk, char name);
void			rrr(t_data *data);
void			push(t_data *data, t_stack **src, t_stack **dest, char name);

void			normalize(t_data *data);
void			select_algorithm(t_data *data);
void			print_bench(t_data *data);
void			putnbr(size_t n);
void			putstr(char *str);
void			select_bench(t_data *data);

void			simple_algorithm(t_data *data);
void			medium_algorithm(t_data *data);
void			complex_algorithm(t_data *data);

#endif
