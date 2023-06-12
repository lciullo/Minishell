/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:50:41 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/12 14:24:45 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_var(char *name_var, t_env *lst_env, char *new_line)
{
	while (lst_env)
	{
		if (ft_strcmp(name_var, lst_env->name) == 0)
		{
			new_line = ft_strjoin_parsing(new_line, lst_env->value);
			if (!(new_line))
				return (NULL);
			return (new_line);
		}
		lst_env = lst_env->next;
	}
	return (new_line);
}

char	*ft_strjoin_b(char*s1, char *s2, int start, int i)
{
	int		j;
	int		k;
	char	*new_s;

	j = 0;
	k = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_s = malloc(sizeof(char) * (ft_strlen(s1) + (i - start) + 1));
	if (!(new_s))
		return (free(s1), NULL);
	while (s1[j])
	{
		new_s[k] = s1[j];
		k++;
		j++;
	}
	while (start < i)
	{
		new_s[k] = s2[start];
		k++;
		start++;
	}
	new_s[k] = '\0';
	return (free(s1), new_s);
}
