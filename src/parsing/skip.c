/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:45:38 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/21 15:47:20 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote(char *line, int *i, char quote)
{
	*i = *i + 1;
	while (line[*i])
	{
		if (*i > 1 && line[*i] == quote && line[*i - 1] == '\\')
			*i = *i + 1;
		else if (line[*i] == quote)
			break ;
		else
			*i = *i + 1;
	}
}

int	skip_white_space(char	*line)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	skip_white_space_2(char	*line, int i)
{
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		i++;
	return (i);
}
int	skip_redir(char *line, int *i, char redir, t_data *data)
{
	int	len;

	len = 0;
	if (line[*i] && line[*i + 1] && line[*i] == '<' && line[*i + 1] == '>')
		return (3);
	while (line[*i] && line[*i] == redir)
	{
		*i = *i + 1;
		len++;
	}
	if (line[*i] == '\0')
		len = 3;
	if (len == 1 && redir == '<')
		data->nbr_input++;
	if (len == 1 && redir == '>')
		data->nbr_output++;
	if (len == 2 && redir == '<')
		data->nbr_here_doc++;
	if (len == 2 && redir == '>')
		data->nbr_append++;
	return (len);
}
