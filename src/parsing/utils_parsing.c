/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/18 10:50:33 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_structure(t_data *data)
{
	data->nbr_pipe = 0;
	data->nbr_quote = 0;
	data->nbr_here_doc = 0;
	data->nbr_append = 0;
	data->len_line = 0;
	data->nbr_input = 0;
	data->nbr_output = 0;
	data->nbr_redir = 0;
	data->start = 0;
	data->end = 0;
}

void	change_tab(char **tab_line)
{
	int		i;
	int		j;
	//char	quote;

	i = 0;
	j = 0;
	while (tab_line[i])
	{
		if (tab_line[i][0] == 34 || tab_line[i][0] == 39)
		{
			j = 0;
			//quote = tab_line[i][0];
			while (tab_line[i][j])
			{
				if (tab_line[i][j] == -1)
					tab_line[i][j] = ' ';
				j++;
			}
			// if (tab_line[i][j - 1] == quote)
			// 	tab_line[i] = delete_quote(tab_line[i], j);
		}
		i++;
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

/*char	*new_line;
	int		i;
	int		k;

	new_line = malloc(sizeof(char) * (j - 2 + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	k = 1;
	while (k < j - 1)
	{		
		new_line[i] = line[k];
		i++;
		k++;
	}
	new_line[i] = '\0';
	return (new_line);*/