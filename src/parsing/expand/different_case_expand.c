/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   different_case_expand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:40:47 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 23:31:24 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_case(t_expand *utils, int *i);
static int	copy_first_part_of_line(t_expand *utils, int *i, int *start);
static int	check_dollar_then_quote_hd(char	*line, int *i, int here_doc);

int	handle_quotes(t_expand *utils, int *i, int *start, int here_doc)
{
	int	rv_dollar_sign;

	rv_dollar_sign = 0;
	if (utils->line[*i] == '\'' && here_doc == 0)
		skip_quote(utils->line, i, utils->line[*i]);
	else if (utils->line[*i] == '\"' || \
	(utils->line[*i] == '\'' && here_doc == 1))
	{
		if (utils->line[*i] == utils->quote)
			*i = *i + 1;
		while (utils->line[*i] && utils->line[*i] != utils->quote)
		{	
			if (if_check(1, utils->line, *i) == true)
			{
				rv_dollar_sign = handle_dollar_sign(utils, i, start, here_doc);
				if (rv_dollar_sign == FAILURE)
					return (FAILURE);
				if (rv_dollar_sign != 3)
					*start = *i;
			}
			else if (utils->line[*i])
				*i = *i + 1;
		}
	}
	return (SUCCESS);
}

int	handle_dollar_sign(t_expand *utils, int *i, int *start, int here_doc)
{
	char	*temp;

	if (*i - *start != 0)
	{
		if (copy_first_part_of_line(utils, i, start) == FAILURE)
			return (FAILURE);
	}
	if (check_dollar_then_quote_hd(utils->line, i, here_doc) == 3)
		return (3);
	else if (utils->line[*i + 1] == '$' || utils->line[*i + 1] == '?')
	{
		temp = utils->new_line;
		if (handle_special_case(utils, i) == FAILURE)
			return (free(temp), FAILURE);
	}
	else if (ft_isalpha(utils->line[*i + 1]) == 1 || utils->line[*i + 1] == '_')
	{
		temp = utils->new_line;
		utils->new_line = get_var(utils, i);
		if (!(utils->new_line))
			return (free(temp), FAILURE);
	}
	else
		*i = *i + 2;
	return (SUCCESS);
}

static int	copy_first_part_of_line(t_expand *utils, int *i, int *start)
{
	char	*temp;

	temp = utils->new_line;
	utils->new_line = ft_strjoin_expand(utils->new_line, \
	utils->line, *start, *i);
	if (!(utils->new_line))
		return (free(temp), FAILURE);
	free(temp);
	return (SUCCESS);
}

static int	handle_special_case(t_expand *utils, int *i)
{
	char	*str_exit_status;

	if (utils->line[*i + 1] == '$')
	{
		utils->new_line = ft_strjoin_parsing(utils->new_line, "$$");
		if (!(utils->new_line))
			return (FAILURE);
		*i = *i + 2;
	}
	else if (utils->line[*i + 1] == '?')
	{
		str_exit_status = ft_itoa(g_exit_status);
		if (!(str_exit_status))
			return (FAILURE);
		utils->new_line = ft_strjoin_parsing(utils->new_line, str_exit_status);
		free(str_exit_status);
		if (!(utils->new_line))
			return (FAILURE);
		*i = *i + 2;
	}
	return (SUCCESS);
}

static int	check_dollar_then_quote_hd(char	*line, int *i, int here_doc)
{
	if (here_doc == 1 && (line[*i + 1] == '\'' || line[*i + 1] == '\"'))
	{
		*i = *i + 2;
		return (3);
	}
	return (SUCCESS);
}
