#include "minishell.h"

void		check_quote_expand(char *s);
static char	*ft_copy_join_parsing(char *s1, char *s2, char *str);

char	*ft_strjoin_parsing(char *s1, char *s2, int type)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (type == 1)
	{
		check_quote_expand(s2);
		ft_dprintf(2, "%s\n", s2);
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
	{
		free((void *)s1);
		return (NULL);
	}
	str = ft_copy_join_parsing(s1, s2, str);
	free(s1);
	return (str);
}

void	check_quote_expand(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			s[i] = -1;
		else if (s[i] == '\'')
			s[i] = -2;
		i++;
	}
}

static char	*ft_copy_join_parsing(char *s1, char *s2, char *str)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
