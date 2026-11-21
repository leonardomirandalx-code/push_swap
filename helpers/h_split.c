#include "push_swap.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
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

void	free_words(char **words, int count)
{
	while (count > 0)
		free(words[--count]);
	free(words);
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
