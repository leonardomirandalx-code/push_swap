#include "push_swap.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

int	count_words(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!is_space(s[i]) && (i == 0 || is_space(s[i - 1])))
			count++;
		i++;
	}
	return (count);
}

static int	fill_words(char **words, char const *s)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		start = i;
		while (s[i] && !is_space(s[i]))
			i++;
		if (i > start)
		{
			words[j] = ft_substr(s, start, i - start);
			if (!words[j])
				return (free_words(words, j), 0);
			j++;
		}
	}
	words[j] = NULL;
	return (1);
}

char	**ft_split(char const *s)
{
	char	**words;

	if (!s)
		return (NULL);
	words = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!words)
		return (NULL);
	if (!fill_words(words, s))
		return (NULL);
	return (words);
}
