/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:59:20 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/15 16:35:29 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_redir(char *line, t_data *data);
void	skip_quote(char *line, int *i, char quote);
int		skip_redir(char *line, int *i, char redir, t_data *data);

int	check_error(char *line, t_data *data)
{
	//quote needs to be checked first
	if (check_redir(line, data) == 1)
		return (1);
	return (0);
}

int	check_redir(char *line, t_data *data)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] == '|')
			data->nbr_pipe++;
		if (line[i] && (line[i] == '<' || line[i] == '>'))
		{
			if (skip_redir(line, &i, line[i], data) > 2)
				return (ft_dprintf(2, "syntax error\n"), 1);
		}
		else 
			i++;
	}
	data->len_line = i;
	data->nbr_redir = data->nbr_here_doc + \
	data->nbr_output + data->nbr_append + data->nbr_input;
	return (0);
}

void	skip_quote(char *line, int *i, char quote)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != quote)
		*i = *i + 1;
}

int	skip_redir(char *line, int *i, char redir, t_data *data)
{
	int	len;

	len = 0;
	while (line[*i] && line[*i] == redir)
	{
		*i = *i + 1;
		len++;
	}
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
