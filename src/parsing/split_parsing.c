#include "minishell.h"

bool	is_white_space(char	c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

static int	ft_count_words_parsing(char const *s)
{
	int	i;
	int	nb_words;
	int	is_valid;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		is_valid = 0;
		while (s[i] && is_white_space(s[i]) == true)
			i++;
		while (s[i] && is_white_space(s[i]) == false)
		{
			is_valid = 1;
			i++;
		}
		if ((s[i] == 0 || is_white_space(s[i]) == true) && is_valid)
			nb_words++;
	}
	return (nb_words);
}

static void	*ft_free_parsing(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_sp_parsing(char const *s, char **tab)
{
	size_t		i;
	size_t		j;
	size_t		start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_white_space(s[i]) == false)
		{
			start = i;
			while (s[i] && is_white_space(s[i]) == false)
				i++;
			tab[j] = ft_substr(s, start, i - start);
			if (!(tab[j]))
				return (ft_free_parsing(tab, j));
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_parsing(char const *s)
{
	char		**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_words_parsing(s) + 1));
	if (!(tab))
		return (NULL);
	return (ft_sp_parsing(s, tab));
}