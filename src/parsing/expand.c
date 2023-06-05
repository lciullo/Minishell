/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:20:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/05 12:52:40 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_expand *utils, int *i);
void	handle_double_quotes(t_expand *utils, int *i, int *start);
void	handle_single_quote(t_expand *utils, int *i);
void	handle_dollar_sign(t_expand *utils, int *i, int *start);

char	*expand(char *line, t_env **lst_env)
{
	int			i;
	int			start;
	t_expand	utils;

	i = 0;
	start = 0;
	utils.line = line;
	utils.env = lst_env;
	utils.new_line = ft_calloc(1, 1);
	if (!(utils.new_line))
		return (NULL);
	while (line[i])
	{
		if (utils.line[i] == '\"')
			handle_double_quotes(&utils, &i, &start);
		else if (line[i] == '\'')
			handle_single_quote(&utils, &i);
		else if (line[i] == '$')
			handle_dollar_sign(&utils, &i, &start);
		else if (line[i])
			i++;
	}
	if (line[start])
		utils.new_line = ft_strjoin_b(utils.new_line, line, start, i);
	return (free(line), utils.new_line);
}

void	handle_double_quotes(t_expand *utils, int *i, int *start)
{
	if (utils->line[*i] == '\"')
		*i = *i + 1;
	while (utils->line[*i])
	{	
		if (utils->line[*i] == '\"')
			break ;
		if (utils->line[*i] == '$')
			handle_dollar_sign(utils, i, start);
		else if (utils->line[*i])
			*i = *i + 1;
	}
	if (utils->line[*i] == '\"')
		*i = *i + 1;
}

void	handle_single_quote(t_expand *utils, int *i)
{
	skip_quote(utils->line, i, utils->line[*i]);
	if (utils->line[*i] == '\'')
		*i = *i + 1;
}

void	handle_dollar_sign(t_expand *utils, int *i, int *start)
{
	utils->new_line = ft_strjoin_b(utils->new_line, utils->line, *start, *i);
	utils->new_line = get_var(utils, i);
	*start = *i;
}

char	*get_var(t_expand *utils, int *i)
{
	int		start;
	int		j;
	char	*name_var;

	j = 0;
	if (utils->line[*i] == '$')
		*i = *i + 1;
	start = *i;
	while (utils->line[*i] && utils->line[*i] != '$' && \
	is_white_space(utils->line[*i]) == false && utils->line[*i] != '\"' \
	&& utils->line[*i] != '\'')
		*i = *i + 1;
	name_var = malloc(sizeof(char) * ((*i - start) + 1));
	if (!(name_var))
		return (NULL);
	while (start < *i)
	{
		name_var[j] = utils->line[start];
		j++;
		start++;
	}
	name_var[j] = '\0';
	utils->new_line = check_var(name_var, utils->env, utils->new_line);
	free(name_var);
	return (utils->new_line);
}
