/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:43:33 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/30 14:39:30 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_list(t_list **list)
{
	t_list	*temp;

	temp = (*list);
	while (temp)
	{
		if (temp->data[0][0] == '>' && temp->data[0][1] == '>')
			temp->next->type = APPEND;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '<')
			temp->next->type = HERE_DOC;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '\0')
			temp->next->type = INFILE;
		else if (temp->data[0][0] == '>' && temp->data[0][1] == '\0')
			temp->next->type = OUTFILE;
		else if (temp->data[0][0] == '|')
			temp->type = PIPE;
		else if (temp->type == -1 && is_builtins(temp->data[0]) == true)
			temp->type = BUILTIN;
		else if (temp->type == -1 && \
		(temp->data[0][0] != '>' || temp->data[0][0] != '<'))
			temp->type = TOKEN;
		temp = temp->next;
	}
}

void	is_there_a_quote(t_list **list)
{
	t_list	*temp;
	int		row;
	int		i;

	temp = (*list);
	while (temp)
	{
		if (temp->type == TOKEN || temp->type == BUILTIN)
		{
			row = 0;
			while (temp->data[row])
			{
				i = 0;
				while (temp->data[row][i])
				{
					if (temp->data[row][i] == '\'' || \
					temp->data[row][i] == '\"')
					{
						temp->data[row] = delete_quote(temp->data[row]);
						break ;
					}
					i++;
				}
				row++;
			}
		}
		temp = temp->next;
	}
}

char	*delete_quote(char *line)
{
	int		i;
	int		j;
	char	quote;
	char	*new_s;

	new_s = NULL;
	new_s = malloc(sizeof(char) * (ft_strlen(line) - (count_quote(line) * 1) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i])
			{
				if (line[i] == quote)
				{
					i++;
					break ;
				}
				else
				{
					new_s[j] = line[i];
					i++;
					j++;
				}
			}
		}
		else
		{
			new_s[j] = line[i];
			i++;
			j++;
		}
	}
	new_s[j] = '\0';
	free(line);
	return (new_s);
}

int	count_quote(char *line)
{
	int		i;
	int		nbr_quote;
	char	quote;

	i = 0;
	nbr_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			nbr_quote++;
			while (line[i])
			{
				if (line[i] == quote)
				{
					i++;
					break ;
				}
				i++;
			}
		}
		else
			i++;
	}
	return (nbr_quote);
}
