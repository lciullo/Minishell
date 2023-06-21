/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_we_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:51:38 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/21 20:50:28 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand);
char		*join_tab(char **tab);
int	expand_data(t_list *temp, t_env *env, int *status_expand);
int	process_expanded_data(t_list *temp);
int	handle_tilde(char **tab, int i);
int	launch_expand(t_env *env, char **tab, int i, int *status_expand);

int	should_we_expand(t_list **list, t_env *env)
{
	t_list	*temp;
	int		status_expand;

	temp = (*list);
	status_expand = 0;
	while (temp)
	{
		if (temp->type != HERE_DOC)
		{
			if (expand_data(temp, env, &status_expand) == FAILURE)
				return (ft_lstclear(list, free), FAILURE);
			if (status_expand == 1 && temp->data[1] != NULL)
			{
				if (process_expanded_data(temp) == FAILURE)
					return (ft_lstclear(list, free), FAILURE);
				status_expand = 0;
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	expand_data(t_list *temp, t_env *env, int *status_expand)
{
	char	**temp_tab;
	
	temp_tab = temp->data;
	temp->data = is_there_a_dollar(temp->data, env, status_expand);
	if (!(temp->data))
	{
		temp->data = temp_tab;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	process_expanded_data(t_list *temp)
{
	char	*tab_in_line;
	char	**temp_tab;
	
	change_tab(temp->data, 0);
	temp_tab = temp->data;
	tab_in_line = join_tab(temp->data);
	if (!(tab_in_line))
	{
		temp->data = temp_tab;
		return (FAILURE);
	}
	temp_tab = temp->data;
	temp->data = ft_split_parsing(tab_in_line);
	if (!(temp->data))
	{
		temp->data = temp_tab;
		return (free(tab_in_line), FAILURE);
	}
	free(temp_tab);
	change_tab(temp->data, 1);
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
		new_s = ft_strjoin_parsing(new_s, tab[i]);
		if (!new_s)
			return (NULL);
		new_s = ft_strjoin_parsing(new_s, " ");
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
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '$' || tab[i][j] == '~')
			{
				if (handle_tilde(tab, i) == FAILURE)
					return (NULL);
				if (launch_expand(env, tab, i, status_expand) == FAILURE)
					return (NULL);
				break ;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

int	launch_expand(t_env *env, char **tab, int i, int *status_expand)
{
	char *temp;
	
	temp = tab[i];
	tab[i] = expand(tab[i], env, 0, 0);
	if (!(tab[i]))
		return (FAILURE);
	free(temp);
	*status_expand = 1;
	return (SUCCESS);
}

int	handle_tilde(char **tab, int i)
{
	char *temp;
	
	if (tab[i][0] == '~' && tab[i][1] == '\0')
	{	
		temp = tab[i];
		tab[i] = ft_strdup("$HOME");//securiser
		if (!tab[i])
			return (FAILURE);
		free(temp);
	}
	else if (tab[i][0] == '~' && tab[i][1] != '\0')
	{
		temp = tab[i];
		tab[i] = ft_strjoin_expand("$HOME", tab[i], 1, ft_strlen(tab[i]));
		if (!tab[i])
			return (FAILURE);
		free(temp);
	}
	return (SUCCESS);
}
