/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/17 12:20:11 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reput_space(char **tab_line, int *i, int *j);

void	init_structure(t_data *data, t_env *lst_env, char *line)
{
	data->nbr_pipe = 0;
	data->nbr_quote = 0;
	data->nbr_here_doc = 0;
	data->nbr_append = 0;
	data->len_line = 0;
	data->nbr_infile = 0;
	data->nbr_outfile = 0;
	data->nbr_redir = 0;
	data->start = 0;
	data->end = 0;
	data->lst_env = lst_env;
	data->line = line;
}

void	change_tab(char **tab_line, int type)
{
	int		i;
	int		j;

	i = 0;
	while (tab_line[i])
	{
		j = 0;
		if (type == 2)
			change_quote(tab_line[i], 1);
		else
		{
			while (tab_line[i][j])
			{
				if ((tab_line[i][j] == '\'' || tab_line[i][j] == '\"') && type == 0)
					replace_space(tab_line[i], 0);
				else if ((tab_line[i][j] == '\'' || tab_line[i][j] == '\"') && type == 1)
					reput_space(tab_line, &i, &j);
				if (tab_line[i][j] != '\0')
					j++;
			}
		}
		i++;
	}
}

static void	reput_space(char **tab_line, int *i, int *j)
{
	char	quote;

	quote = tab_line[*i][*j];
	*j = *j + 1;
	while (tab_line[*i][*j])
	{
		if (tab_line[*i][*j] == quote)
			break ;
		if (tab_line[*i][*j] == -1)
			tab_line[*i][*j] = ' ';
		*j = *j + 1;
	}
}

bool	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
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
	// str[i] == '\n'
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
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
		else if (s[i] =='\'')
			s[i] = -2;
		i++;
	}
}

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
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)); // +2
	if (!str)
	{
		free((void *)s1);
		return (NULL);
	}
	str = ft_copy_join_parsing(s1, s2, str);
	free(s1);
	return (str);
}