/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:42:15 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 16:44:00 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_of_expand(t_expand *utils, int i, int start);
static int	prepare_handles_quote(t_expand *utils, int *i, \
int *start, int here_doc);

char	*expand(t_expand *utils, int i, int start, int here_doc)
{
	int	rv_dollar_sign;

	rv_dollar_sign = 0;
	while (utils->line[i])
	{
		if (utils->line[i] == '\"' || utils->line[i] == '\'')
		{
			if (prepare_handles_quote(utils, &i, &start, here_doc) == FAILURE)
				return (NULL);
		}
		else if (if_check(0, utils->line, i) == true)
		{
			rv_dollar_sign = handle_dollar_sign(utils, &i, &start, here_doc);
			if (rv_dollar_sign == FAILURE)
				return (NULL);
			if (rv_dollar_sign != 3)
				start = i;
		}
		else if (utils->line[i])
			i++;
	}
	if (end_of_expand(utils, i, start) == FAILURE)
		return (NULL);
	return (utils->new_line);
}

static int	prepare_handles_quote(t_expand *utils, int *i, int *start, \
int here_doc)
{
	utils->quote = utils->line[*i];
	if (handle_quotes(utils, i, start, here_doc) == FAILURE)
		return (FAILURE);
	if (utils->line[*i] == utils->quote)
		*i = *i + 1;
	return (SUCCESS);
}

static int	end_of_expand(t_expand *utils, int i, int start)
{
	char	*temp;

	if (utils->line[start])
	{
		temp = utils->new_line;
		utils->new_line = ft_strjoin_expand(utils->new_line, \
		utils->line, start, i);
		free(temp);
		if (!utils->new_line)
			return (FAILURE);
	}
	return (SUCCESS);
}
