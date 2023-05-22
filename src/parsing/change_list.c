/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:43:33 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/18 11:36:04 by cllovio          ###   ########.fr       */
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
			while(temp->data[row])
			{
				i = 0;
				while(temp->data[row][i])
				{
					if (temp->data[row][i] == '\'' || temp->data[row][i] == '\"')
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
	char	nbr_quote;
	char	*new_s;

	i = 0;
	nbr_quote = 0;
	new_s = NULL;
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
	new_s = malloc(sizeof(char) * (ft_strlen(line) - (nbr_quote * 1) + 1));
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
			nbr_quote++;
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

char	**change_order(char **tab)
{
	int		tab_size;
	char	**new_tab;
	int		end;
	int		start;
	int		i;

	tab_size = 0;
	end = 0;
	start = 0;
	i = 0;
	while (tab[tab_size])
		tab_size++;
	new_tab = malloc(sizeof(char *) * (tab_size + 1));
	if (!new_tab)
		return (NULL);
	while (tab[end])
	{
		if (tab[end][0] == '|' || tab[end + 1] == NULL)
		{
			change_order_redir(new_tab, tab, start, end, &i);
			start = end + 1;
		}
		end++;
	}
	new_tab[end] = NULL;
	free_array(tab);
	return (new_tab);
}

void	change_order_redir(char **new_tab, char **tab, \
int start, int end, int *i)
{
	int	start_b;

	start_b = start;
	while (start < end)
	{
		if (tab[start][0] == '<' || tab[start][0] == '>')
		{
			new_tab[*i] = ft_strdup(tab[start]);
			*i = *i + 1;
			start++;
			new_tab[*i] = ft_strdup(tab[start]);
			*i = *i + 1;
		}
		start++;
	}
	change_order_token(new_tab, tab, start_b, end, i);
}

void	change_order_token(char **new_tab, char **tab, \
int start, int end, int *i)
{
	while (start <= end)
	{
		if (tab[start][0] == '<' || tab[start][0] == '>')
			start++;
		if (start > 0 && (tab[start - 1][0] == '<' || tab[start - 1][0] == '>'))
			start++;
		else
		{
			new_tab[*i] = ft_strdup(tab[start]);
			*i = *i + 1;
			start++;
		}
	}
}
