/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:20:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/26 15:20:54 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_b(char*s1, char *s2, int start, int i);
char	*get_var_quote(char *line, int *i, t_env **lst_env, \
		char *new_line, int *start);
char	*get_var(char *line, int *i, t_env **lst_env, char *new_line);
char	*check_var(char *name_var, t_env **lst_env, char *new_line);

char	*expand(char *line, t_env **lst_env)
{
	int		i;
	int		start;
	char	*new_line;

	i = 0;
	start = 0;
	new_line = malloc(sizeof(char));
	if (!new_line)
		return (NULL);
	new_line[0] = '\0';
	while (line[i])
	{
		if (line[i] == '\"')
			new_line = get_var_quote(line, &i, lst_env, new_line, &start);
		if (line[i] == '\'')
		{
			skip_quote(line, &i, line[i]);
			if (line[i] == '\'')
				i++;
		}
		if (line[i] == '$')
		{
			new_line = ft_strjoin_b(new_line, line, start, i);
			new_line = get_var(line, &i, lst_env, new_line);
			start = i;
		}
		else if (line[i])
			i++;
	}
	if (line[start])
		new_line = ft_strjoin_b(new_line, line, start, i);
	free(line);
	ft_dprintf(2, "line : %s\n", new_line);
	return (new_line);
}

char	*get_var_quote(char *line, int *i, t_env **lst_env, \
		char *new_line, int *start)
{
	if (line[*i] == '\"')
		*i = *i + 1;
	while (line[*i])
	{	
		if (line[*i] == '\"')
			break ;
		if (line[*i] == '$')
		{
			ft_dprintf(2, "start : %d i : %i\n", *start, *i);
			new_line = ft_strjoin_b(new_line, line, *start, *i);
			new_line = get_var(line, i, lst_env, new_line);
			ft_dprintf(2, "start : %d i : %i\n", *start, *i);
			*start = *i;
		}
		else if (line[*i])
			*i = *i + 1;
	}
	if (line[*i] == '\"')
		*i = *i + 1;
	return (new_line);
}

char	*get_var(char *line, int *i, t_env **lst_env, char *new_line)
{
	int		start;
	int		j;
	char	*name_var;

	j = 0;
	if (line[*i] == '$')
		*i = *i + 1;
	start = *i;
	while (line[*i] && line[*i] != '$' && is_white_space(line[*i]) == false \
	&& line[*i] != '\"' && line[*i] != '\'')
		*i = *i + 1;
	name_var = malloc(sizeof(char) * ((*i - start) + 1));
	if (!(name_var))
		return (NULL);
	while (start < *i)
	{
		name_var[j] = line[start];
		j++;
		start++;
	}
	name_var[j] = '\0';
	new_line = check_var(name_var, lst_env, new_line);
	free(name_var);
	return (new_line);
}

char	*check_var(char *name_var, t_env **lst_env, char *new_line)
{
	while (*lst_env)
	{
		if (ft_strcmp(name_var, (*lst_env)->name) == 0)
		{
			new_line = ft_strjoin(new_line, (*lst_env)->value);
			return (new_line);
		}
		(*lst_env) = (*lst_env)->next;
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
		return (NULL);
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
	return (new_s);
}
