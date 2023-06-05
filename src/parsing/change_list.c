/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:43:33 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/05 16:27:47 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_quote_content(char *new_s, char *line, int *i, int *j);
int		get_nbr_quote(char *line);
void	is_there_a_quote(char *row);
char	*delete_quote(char *row);
int		get_nbr_quote(char *row);
void	copy_quote_content(char *new_s, char *row, int *i, int *j);

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

void	parse_line_for_quote(t_list **list)
{
	t_list	*temp;
	int		r;

	temp = (*list);
	while (temp)
	{
		if (temp->type == TOKEN || temp->type == BUILTIN)
		{
			r = 0;
			while (temp->data[r])
			{
				temp->data[r] = is_there_quote(temp->data[r]);
				r++;
			}
		}
		temp = temp->next;
	}
}

void	is_there_a_quote(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] == '\'' || row[i] == '\"')
		{
			row = delete_quote(row);
			break ;
		}
		i++;
	}
	return (row);
}

char	*delete_quote(char *row)
{
	int		i;
	int		j;
	char	*new_s;

	new_s = malloc(sizeof(char) * \
			(ft_strlen(row) - (get_nbr_quote(row) * 1) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (row[i])
	{
		if (row[i] == '\'' || row[i] == '\"')
			copy_quote_content(new_s, row, &i, &j);
		else
		{
			new_s[j] = row[i];
			i++;
			j++;
		}
	}
	new_s[j] = '\0';
	free(row);
	return (new_s);
}

int	get_nbr_quote(char *row)
{
	int		nbr_quote;
	int		i;
	char	quote;

	nbr_quote = 0;
	i = 0;
	while (row[i])
	{
		if (row[i] == '\'' || row[i] == '\"')
		{
			quote = row[i++];
			nbr_quote++;
			while (row[i++])
			{
				if (row[i] == quote)
				{
					i++;
					break ;
				}
			}
		}
		else
			i++;
	}
	return (nbr_quote);
}

void	copy_quote_content(char *new_s, char *row, int *i, int *j)
{
	char	quote;

	quote = row[*i];
	*i = *i + 1;
	while (row[*i])
	{
		if (row[*i] == quote)
		{
			*i = *i + 1;
			break ;
		}
		else
		{
			new_s[*j] = row[*i];
			*i = *i + 1;
			*j = *j + 1;
		}
	}
}
