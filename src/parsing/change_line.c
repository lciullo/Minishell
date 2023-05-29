/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:08:31 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/29 15:24:41 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_line(t_data *data)
{
	char	*new_line;

	new_line = expand(data->line, data->lst_env);
	if (!new_line)
		return (NULL);
	replace_space(new_line, data, 0);
	return (new_line);
}

void	replace_space(char *line, t_data *data, int i)
{
	int		check_quote;
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			check_quote = 0;
			quote = line[i++];
			while (line[i++] && check_quote == 0)
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
		if (line[i])
			i++;
	}
}
