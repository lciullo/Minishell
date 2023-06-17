/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_we_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:51:38 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/17 10:50:53 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand);
char		*join_tab(char **tab);

int	should_we_expand(t_list **list, t_env *env)
{
	t_list	*temp;
	char	*tab_in_line;
	char	**temp_tab;
	int		status_expand;

	temp = (*list);
	status_expand = 0;
	//print_list(*list);
	while (temp)
	{
		if (temp->type != HERE_DOC)
		{
			temp_tab = temp->data;
			temp->data = is_there_a_dollar(temp->data, env, &status_expand);
			if (!(temp->data))
			{
				temp->data = temp_tab;
				return (ft_lstclear(list, free), FAILURE);
			}
			if (status_expand == 1 && temp->data[0][0] != '\0')
			{
				change_tab(temp->data, 0);
				temp_tab = temp->data;
				tab_in_line = join_tab(temp->data);
				if (!(tab_in_line))
				{
					temp->data = temp_tab;
					return (ft_lstclear(list, free), FAILURE);
				}
				temp_tab = temp->data;
				temp->data = ft_split_parsing(tab_in_line); //leaks en null check
				if (!(temp->data))
				{
					temp->data = temp_tab;
					return (ft_lstclear(list, free), free(tab_in_line), FAILURE);
				}
				free(temp_tab);
				change_tab(temp->data, 1);
				status_expand = 0;
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

char	*join_tab(char **tab)
{
	int		i;
	char	*new_s;

	new_s = calloc(1, 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_s = ft_strjoin_parsing(new_s, tab[i], 0);
		if (!new_s)
			return (NULL);
		new_s = ft_strjoin_parsing(new_s, " ", 0);
		if (!new_s)
			return (NULL);
		i++;
	}
	return (new_s);
}

static char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '$' || tab[i][j] == '~')
			{
				if (tab[i][0] == '~' && tab[i][1] == '\0')
				{	
					temp = tab[i];
					tab[i] = ft_strdup("$HOME");//securiser
					if (!tab[i])
						return (NULL);
					free(temp);
				}
				else if (tab[i][0] == '~' && tab[i][1] != '\0')
				{
					temp = tab[i];
					tab[i] = ft_strjoin_b("$HOME", tab[i], 1, ft_strlen(tab[i]));
					if (!tab[i])
						return (NULL);
					free(temp);
				}
				temp = tab[i];
				tab[i] = expand(tab[i], env);
				if (!(tab[i]))
					return (NULL);
				free(temp);
				*status_expand = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (tab);
}
