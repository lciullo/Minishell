/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:20:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/21 19:37:06 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_dollar_sign(t_expand *utils, int *i, int *start);
static char	*get_var(t_expand *utils, int *i);
int	handle_quotes(t_expand *utils, int *i, int *start);
void	end_of_expand(t_expand *utils, int i, int start);
int	handle_special_case(t_expand *utils, int *i);

bool	if_check(int type, char *line, int i)
{
	if (type == 0 && (line[i] == '$' && (ft_isalnum(line[i + 1]) == true || \
		line[i + 1] == '_' || line[i + 1] == '?' || line[i + 1] == '\'' \
		|| line[i + 1] == '\"' || line[i + 1] == '$')))
			return (true);
	if (type == 1 && (line[i] == '$' && (ft_isalnum(line[i + 1]) == true \
	|| line[i + 1] == '_' || line[i + 1] == '?' || line[i + 1] == '$')))
		return (true);
	return (false);
}

void	init_struct_expand(char *line, t_env *lst_env, t_expand *utils)
{
	utils->line = line;
	utils->env = lst_env;
	utils->new_line = ft_calloc(1, 1);
}
	
char	*expand(char *line, t_env *lst_env, int i, int start)
{
	t_expand	utils;

	init_struct_expand(line, lst_env, &utils);
	if (!utils.line)
		return (free(line),NULL);
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
	end_of_expand(&utils, i, start); //je securise ?
	return (utils.new_line);
}


void	end_of_expand(t_expand *utils, int i, int start)
{
	char	*temp;
	
	if (utils->line[start])
	{
		temp = utils->new_line;
		utils->new_line = ft_strjoin_expand(utils->new_line, utils->line, start, i);//securiser
		if (utils->new_line)
			free(temp);
	}
}

int	handle_quotes(t_expand *utils, int *i, int *start)
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

int	handle_special_case(t_expand *utils, int *i)
{
	if (utils->line[*i + 1] == '$')
	{
		utils->new_line = ft_strjoin_parsing(utils->new_line, "$$");
		if (!(utils->new_line))
			return (FAILURE);
		*i = *i + 2;
	}
	else if (utils->line[*i + 1] == '?')
	{
		utils->new_line = ft_strjoin_parsing(utils->new_line, ft_itoa(g_exit_status));
		if (!(utils->new_line))
			return (FAILURE);
		*i = *i + 2;
	}
	return (SUCCESS);
}

static char	*get_var(t_expand *utils, int *i)
{
	int		start;
	int		j;
	char	*name_var;

	j = 0;
	if (utils->line[*i] == '$')
		*i = *i + 1;
	start = *i;
	while (utils->line[*i] && (ft_isalnum(utils->line[*i]) == true \
	|| utils->line[*i] == '_'))
		*i = *i + 1;
	name_var = malloc(sizeof(char) * ((*i - start) + 1));
	if (!(name_var))
		return (free(utils->new_line), NULL);
	while (start < *i)
	{
		name_var[j] = utils->line[start];
		j++;
		start++;
	}
	name_var[j] = '\0';
	utils->new_line = check_var(name_var, utils->env, utils->new_line);
	if (!(utils->new_line))
		return (free(name_var), NULL);
	return (free(name_var), utils->new_line);
}
