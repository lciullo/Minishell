/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:19:23 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:22:59 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_unset(char *value);
static void	search_and_delete(char *name, t_env **lst);
static int	is_valid(int c);

void	implement_unset(char **token, t_env **lst)
{
	int	i;
	int	exit_status;
	int	previous_exit_status;

	i = 1;
	exit_status = 0;
	previous_exit_status = 0;
	if (!lst)
		return ;
	while (token[i] != NULL)
	{
		if (i != 1)
			previous_exit_status = exit_status;
		exit_status = parse_unset(token[i]);
		if (exit_status == 0)
			search_and_delete(token[i], lst);
		if (previous_exit_status != 0 && exit_status == 0)
			exit_status = previous_exit_status;
		i++;
	}
	g_exit_status = exit_status;
	return ;
}

static void	search_and_delete(char *name, t_env **lst)
{
	t_env	*index;
	t_env	*prev;

	index = *lst;
	prev = NULL;
	while (index)
	{
		if (!ft_strcmp(index->name, name))
		{
			if (prev)
				prev->next = index->next;
			else
				*lst = index->next;
			if (index->name)
				free(index->name);
			if (index->value)
				free(index->value);
			free(index);
			return ;
		}
		prev = index;
		index = index->next;
	}
}

static int	is_valid(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z') || (c == '_'))
		return (SUCCESS);
	else
		return (FAILURE);
}

static int	parse_unset(char *value)
{
	size_t	i;

	i = 0;
	if (!value || value[0] == '\0')
		return (ft_putstr_fd("unset : not a valid identifier\n", 2), 1);
	if (value[0] != '\0')
	{
		if (value[0] == '-')
			return (ft_putstr_fd("subject : unset with no options\n", 2), 2);
		if (first_char(value[0]) == FAILURE)
			return (ft_putstr_fd("unset : not a valid identifier\n", 2), 1);
	}
	while (value[i] != '\0')
	{
		if (is_valid(value[i]) == FAILURE)
			return (ft_putstr_fd("unset : not a valid identifier\n", 2), 1);
		i++;
	}
	return (0);
}
