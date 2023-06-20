/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:51:19 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/17 17:58:06 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_array_env(char **env, size_t row)
{
	size_t	i;

	i = 0;
	while (i < row + 1)
	{
		free(env[i]);
		i++;
	}
	free(env);
	return ;
}

static size_t	get_nb_row(t_env *lst)
{
	size_t	nb_row;

	nb_row = 0;
	if (!lst)
		return (FAILURE);
	while (lst != NULL)
	{
		if (lst->equal == TRUE)
			nb_row++;
		lst = lst->next;
	}
	return (nb_row);
}

static	char	*join_name_with_value(char *name, char *value, int *malloc_check)
{
	char	*start;
	char	*tmp_name;
	char	*result;

	tmp_name = ft_strdup(name);
	if (!tmp_name)
	{
		*malloc_check = -1;
		perror("Malloc failed in join name with value (ft_strdup)");
		return (NULL);
	}
	start = ft_strjoin(tmp_name, "=");
	if (!start)
	{
		free(tmp_name);
		perror("Malloc failed in join name with value (first ft_strjoin)");
		*malloc_check = -1;
		return (NULL);
	}
	result = ft_strjoin(start, value);
	if (!result)
	{
		free(tmp_name);
		free(start);
		perror("Malloc failed in join name with value (second ft_strjoin)");
		*malloc_check = -1;
		return (NULL);
	}
	free(start);
	free(tmp_name);
	return (result);
}

static char	**make_array(t_env *lst, char **env, int *malloc_check)
{
	size_t	row;

	row = 0;
	while (lst != NULL)
	{
		if (lst->equal == TRUE)
		{
			env[row] = join_name_with_value(lst->name, lst->value, malloc_check);
			if (!env[row])
			{
				perror("Malloc failed in join name with value return function");
				*malloc_check = -1;
				free_array_env(env, row);
				return (NULL);
			}
			row++;
		}
		lst = lst->next;
	}
	env[row] = NULL;
	return (env);
}

char	**fill_env(t_env *lst, int *malloc_check)
{
	char	**env;
	size_t	nb_row;

	if (!lst)
		return (NULL);
	env = NULL;
	nb_row = get_nb_row(lst);
	if (nb_row == 0)
		return (NULL);
	env = malloc(sizeof(char *) * (nb_row + 1));
	if (!env)
		return (NULL);
	env = make_array(lst, env, malloc_check);
	{
		if (!env)
		{
			*malloc_check = -1;
			return (NULL);
		}
	}
	return (env);
}
