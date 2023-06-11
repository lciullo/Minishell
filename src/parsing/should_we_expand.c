/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_we_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:51:38 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/10 19:34:32 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand);
char		*join_tab(char **tab);

void	should_we_expand(t_list **list, t_env *env)
{
	t_list	*temp;
	char	*tab_in_line;
	int		status_expand;

	temp = (*list);
	status_expand = 0;
	while (temp)
	{
		if (temp->type != HERE_DOC)
		{
			temp->data = is_there_a_dollar(temp->data, env, &status_expand);
			if (status_expand == 1 && temp->data[0][0] != '\0')
			{
				change_tab(temp->data, 0);
				tab_in_line = join_tab(temp->data);
				temp->data = ft_split_parsing(tab_in_line);
				change_tab(temp->data, 1);
				free(tab_in_line);
				status_expand = 0;
			}
		}
		temp = temp->next;
	}
}

char	*join_tab(char **tab)
{
	int		i;
	char	*temp;
	char	*new_s;

	new_s = calloc(1, 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		temp = new_s;
		new_s = ft_strjoin(new_s, tab[i]);
		if (!new_s)
			return (NULL);
		free(temp);
		temp = new_s;
		new_s = ft_strjoin(new_s, " ");
		if (!new_s)
			return (NULL);
		free(temp);
		i++;
	}
	free_array(tab);
	return (new_s);
}

static char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '$')
			{
				tab[i] = expand(tab[i], env);
				*status_expand = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (tab);
}
