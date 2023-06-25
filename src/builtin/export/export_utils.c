/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:18:08 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 16:18:11 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	len_according_cases(int len, t_export *stat);

char	*remove_plus_in_name(char *name)
{
	char	*to_find;

	to_find = NULL;
	if (last_char(name) == PLUS)
	{
		to_find = ft_strndup(to_find, name, (unsigned int)ft_strlen(name) - 1);
		if (!to_find)
			return (NULL);
		return (to_find);
	}
	return (name);
}

static	int	len_according_cases(int len, t_export *stat)
{
	if (stat->plus == TRUE && stat->equal == TRUE)
		return (len - 1);
	else if (stat->plus == FALSE && stat->equal == TRUE)
		return (len);
	else if (stat->plus == FALSE && stat->equal == FALSE)
		return (len);
	return (FAILURE);
}

int	len_of_name(char *row, t_export *stat)
{
	int	len;

	len = 0;
	if (row[0] == '\0')
	{
		write(2, "export : not a valid identifier\n", 32);
		g_exit_status = 1;
		return (FAILURE);
	}
	while (row[len] != '\0' && row[len] != '=')
		len++;
	if (row[len] != '\0' && row[len] == '=')
		stat->equal = TRUE;
	if (row[len - 1] != '\0' && row[len - 1] == '+')
		stat->plus = TRUE;
	if (stat->equal == FALSE && stat->plus == TRUE)
	{
		write(2, "export : not a valid identifier\n", 32);
		g_exit_status = 1;
		return (FAILURE);
	}
	len = len_according_cases(len, stat);
	return (len);
}

void	change_equal_to_one(t_env **lst, char *name)
{
	while (*lst != NULL)
	{
		if ((ft_strcmp((*lst)->name, name) == 0))
		{
			if ((*lst)->equal == 0)
				(*lst)->equal = 1;
		}
		*lst = (*lst)->next;
	}
}
