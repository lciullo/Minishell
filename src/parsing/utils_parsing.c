/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/24 13:13:28 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_structure(t_parsing *parsing)
{
	parsing->nbr_pipe = 0;
	parsing->nbr_quote = 0;
	parsing->nbr_here_doc = 0;
	parsing->nbr_append = 0;
	parsing->len_line = 0;
	parsing->nbr_input = 0;
	parsing->nbr_output = 0;
	parsing->nbr_redir = 0;
	parsing->start = 0;
	parsing->end = 0;
}

void	count_separator(char **line, t_parsing *parsing)
{
	while(line[0][parsing->len_line])
	{
		if (line[0][parsing->len_line] == 34 || line[0][parsing->len_line] == 39)
			parsing->nbr_quote++;
		else if (line[0][parsing->len_line] == '|')
			parsing->nbr_pipe++;
		else if (line[0][parsing->len_line] == '<' && line[0][parsing->len_line + 1] == '<')
		{
			parsing->nbr_here_doc++;
			parsing->nbr_redir++;
		}
		else if (line[0][parsing->len_line] == '>' && line[0][parsing->len_line + 1] == '>')
		{
			parsing->nbr_append++;
			parsing->nbr_redir++;
		}
		else if (line[0][parsing->len_line] == '<' && line[0][parsing->len_line - 1] != '<')
		{
			parsing->nbr_input++;
			parsing->nbr_redir++;
		}
		else if (line[0][parsing->len_line] == '>' && line[0][parsing->len_line - 1] != '>')
		{
			parsing->nbr_output++;
			parsing->nbr_redir++;
		}
		parsing->len_line++;
	}
}
