/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:08:31 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/06 13:11:07 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_space(char *line, t_data *data, int i);

char	*change_line(t_data *data)
{
	char	*new_line;

	new_line = add_space(data->line, data);
	if (!new_line)
		return (NULL);
	new_line = expand(new_line, data->lst_env);
	if (!new_line)
		return (NULL);
	replace_space(new_line, data, 0);
	return (new_line);
}

static void	replace_space(char *line, t_data *data, int i)
{
	int		check_quote;
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			check_quote = 0;
			quote = line[i];
			while (line[++i] && check_quote == 0)
			{
				if (line[i] == quote)
				{
					check_quote = 1;
					break ;
				}
				else if (line[i] == ' ')
					line[i] = -1;
				if (line[i] == '\'' || line[i] == '\"')
					data->nbr_quote--;
			}
		}
		if (line[i] != '\0')
			i++;
	}
}
