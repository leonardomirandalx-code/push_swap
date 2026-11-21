#include "push_swap.h"

int	h_atoi(const char *str, int *number)
{
	size_t		i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && result > (long long)INT_MAX + 1))
			return (1);
		i++;
	}
	*number = (int)(result * sign);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void putstr(char *str)
{
    while (*str)
    {
        write(2, str, 1);
        str++;
    }
}

void putnbr(size_t n)
{
    if (n >= 10)
        putnbr(n / 10);
    write(2, &DEC[n % 10], 1);
}