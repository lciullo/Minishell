/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:20:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/22 11:03:52 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	end_of_expand(t_expand *utils, int i, int start);
static int	handle_quotes(t_expand *utils, int *i, int *start);
static int	handle_dollar_sign(t_expand *utils, int *i, int *start);
static int	handle_special_case(t_expand *utils, int *i);

//je securise end_of_Expand 
char	*expand(char *line, t_env *lst_env, int i, int start)
{
	t_expand	utils;

	init_struct_expand(line, lst_env, &utils);
	if (!utils.line)
		return (free(line), NULL);
	if (!lst_env)
		return (NULL);
	while (utils.line[i])
	{
		if (utils.line[i] == '\"' || utils.line[i] == '\'')
		{
			if (handle_quotes(&utils, &i, &start) == FAILURE)
				return (NULL);
		}
		else if (if_check(0, line, i) == true)
		{
			if (handle_dollar_sign(&utils, &i, &start) == FAILURE)
				return (NULL);
			start = i;
		}
		else if (utils.line[i])
			i++;
	}
	end_of_expand(&utils, i, start);
	return (utils.new_line);
}

static void	end_of_expand(t_expand *utils, int i, int start)
{
	char	*temp;

	if (utils->line[start])
	{
		temp = utils->new_line;
		utils->new_line = ft_strjoin_expand(utils->new_line, \
		utils->line, start, i);
		if (utils->new_line)
			free(temp);
	}
}

static int	handle_quotes(t_expand *utils, int *i, int *start)
{
	if (utils->line[*i] == '\'')
	{
		skip_quote(utils->line, i, utils->line[*i]);
		if (utils->line[*i] == '\'')
			*i = *i + 1;
	}
	else if (utils->line[*i] == '\"')
	{
		if (utils->line[*i] == '\"')
			*i = *i + 1;
		while (utils->line[*i] && utils->line[*i] != '\"')
		{	
			if (if_check(1, utils->line, *i) == true)
			{
				if (handle_dollar_sign(utils, i, start) == FAILURE)
					return (FAILURE);
				*start = *i;
			}
			else if (utils->line[*i])
				*i = *i + 1;
		}
		if (utils->line[*i] == '\"')
			*i = *i + 1;
	}
	return (SUCCESS);
}

static int	handle_dollar_sign(t_expand *utils, int *i, int *start)
{
	char	*temp;

	if (*i - *start != 0)
	{
		temp = utils->new_line;
		utils->new_line = ft_strjoin_expand(utils->new_line, \
		utils->line, *start, *i);
		free(temp);
		if (!(utils->new_line))
			return (FAILURE);
	}
	if (utils->line[*i + 1] == '$' || utils->line[*i + 1] == '?')
	{
		if (handle_special_case(utils, i) == FAILURE)
			return (free(utils->line), FAILURE);
	}
	else if (ft_isalpha(utils->line[*i + 1]) == 1 || utils->line[*i + 1] == '_')
	{
		utils->new_line = get_var(utils, i);
		if (!(utils->new_line))
			return (free(utils->line), FAILURE);
	}
	else
		*i = *i + 2;
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
