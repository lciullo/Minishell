/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:20:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/24 14:27:46 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_var_quote(char *line, int *i, t_env **lst_env);
void	get_var(char *line, int *i, t_env **lst_env);
bool	check_var(char *name_var, t_env **lst_env);

void	expand(char *line, t_env **lst_env)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			get_var_quote(line, &i, lst_env);
		else if (line[i] == '\'')
		{
			skip_quote(line, &i, line[i]);
			if (line[i] == '\'')
				i++;
		}
		else if (line[i] == '$') 
			get_var(line, &i, lst_env);
		else if (line[i])
			i++;
	}
}

void	get_var_quote(char *line, int *i, t_env **lst_env)
{
	if (line[*i] == '\"')
		*i = *i + 1;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '$')
			get_var(line, i, lst_env);
		*i = *i + 1;
	}
	if (line[*i] == '\"')
		*i = *i + 1;
}

void	get_var(char *line, int *i, t_env **lst_env)
{
	int		start;
	int		j;
	char	*name_var;
	
	j = 0;
	if (line[*i] == '$')
		*i = *i + 1;
	start = *i;
	while (line[*i] && line[*i] != '$' && line[*i] != '\"' && line[*i] != '\'' \
	&& ((line[*i] <= 9 && line[*i] >= 13) || line[*i] != ' '))
		*i = *i + 1;
	name_var = malloc(sizeof(char) * ((*i - start) + 1));
	if (!(name_var))
		return ;
	while (start < *i)
	{
		name_var[j] = line[start];
		j++;
		start++;
	}
	name_var[j] = '\0';
	if (check_var(name_var, lst_env) == true)
		ft_dprintf(2, "it's okay\n");
	ft_dprintf(2, "%s\n", name_var);
	free(name_var);
}

bool	check_var(char *name_var, t_env **lst_env)
{
	while (*lst_env)
	{
		if (ft_strcmp(name_var, (*lst_env)->variable) == 0)
		{
			ft_dprintf(2, "%s\n", (*lst_env)->value);
			return (true);
		}
		(*lst_env) = (*lst_env)->next;
	}
	return (false);
}
