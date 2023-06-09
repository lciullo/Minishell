/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_we_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:51:38 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/09 16:00:29 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand);

void	should_we_expand(t_list **list, t_env *env)
{
	t_list	*temp;
	char	**temp_tab;
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
				temp_tab = temp->data;
				temp->data = ft_split(temp->data[0], ' ');
				free(temp_tab);
				print_tab(temp->data);
				status_expand = 0;
			}
		}
		temp = temp->next;
	}
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
	print_tab(tab);
	return (tab);
}
