/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/05 20:16:36 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reput_space(char **tab_line, int *i, int *j);

void	init_structure(t_data *data, t_env **lst_env, char *line)
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

void	change_tab(char **tab_line)
{
	int		i;
	int		j;

	i = 0;
	while (tab_line[i])
	{
		j = 0;
		while (tab_line[i][j])
		{
			if (tab_line[i][j] == '\'' || tab_line[i][j] == '\"')
				reput_space(tab_line, &i, &j);
			if (tab_line[i][j] != '\0')
				j++;
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
