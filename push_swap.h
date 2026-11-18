#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

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

char			**ft_split(char const *s, char c);
void			free_words(char **words, int count);
int				count_words(char const *s, char c);

int				h_atoi(const char *str, int *number);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
int				ft_strcmp(char *s1, char *s2);

int				is_number(char *str);
int				is_flag(char *str);
int				parse_args(int argc, char **argv, t_options *options, t_stack **stack_a);
int				validation(char **tokens, t_options *op, t_stack **stack_a);

unsigned int	stacksize(t_stack *stk);
t_stack			*find_bottom(t_stack *stk);
void			add_bottom(t_stack **stk, t_stack *new);
void			add_top(t_stack **stk, t_stack *new);
t_stack			*new_stack(int value);

double			compute_disorder(t_stack *a);
void			swap(t_stack **stk);
void			sa(t_stack **a);
void			sb(t_stack **b);
void			ss(t_stack **a, t_stack **b);
void			reverse_rotate(t_stack **stk);
void			rra(t_stack **a);
void			rrb(t_stack **b);
void			rotate(t_stack **stk);
void			ra(t_stack **a);
void			rb(t_stack **b);

#endif
