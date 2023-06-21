/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:50:41 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/21 14:16:09 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_var(char *name_var, t_env *lst_env, char *new_line)
{
	char	*value;

	while (lst_env)
	{
		if (ft_strcmp(name_var, lst_env->name) == 0)
		{
			value = ft_strdup(lst_env->value);//securier
			change_quote(value, 0);
			new_line = ft_strjoin_parsing(new_line, value);
			if (!(new_line))
				return (NULL);
			return (new_line);
		}
		lst_env = lst_env->next;
	}
	return (new_line);
}

void	change_quote(char *value, int type)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (type == 0)
		{
			if (value[i] == '\"')
				value[i] = -1;
			else if (value[i] == '\'')
				value[i] = -2;
		}
		if (type == 1)
		{
			if (value[i] == -1)
				value[i] = '\"';
			if (value[i] == -2)
				value[i] = '\'';
		}
		i++;
	}
}
