#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <limits.h>

typedef struct	s_stack
{
	int	value;
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

typedef enum e_token_type
{
	INVALID,
	NUMBER,
	FLAG
}	t_token_type;

char	**ft_split(char const *s, char c);
int	h_atoi(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int	ft_strcmp(char *s1, char *s2);
int	is_number(char *str);
int	is_flag(char *str);
unsigned int	ft_stacksize(t_stack *stk);
t_stack	*ft_stacklast(t_stack *stk);
void	ft_stackadd_bottom(t_stack **stk, t_stack *new);
t_stack	*ft_stacknew(int value);
double	compute_disorder(t_stack *a);

#endif
