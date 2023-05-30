/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:40:57 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/30 09:03:38 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static	int	dup_for_one_builtin(t_exec *data)
{
	if (data->infile > 2)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "dup infile issu\n");
			return (-1);
		}
		ft_close(data->infile);
	}
	if (data->outfile > 2)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			ft_dprintf(2, "dup outfile issu\n");
			return (-1);
		}
		ft_close(data->outfile);
	}
	return (0);
}

static	int	to_fork(char **token)
{
	if (!token[0])
		return (0);
	if (ft_strcmp(token[0], "echo") == 0)
		return (1);
	if (ft_strcmp(token[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(token[0], "env") == 0)
		return (1);
	else if (ft_strcmp(token[0], "export") == 0)
	{
		if (!token[1])
			return (1);
		else
			return (0);
	}
	else if (ft_strcmp(token[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(token[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(token[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(token[0], "env") == 0)
		return (0);
	return (0);
}*/

int	one_builtin_exec(t_list *list, char **token, t_exec *data, t_env *lst_env)
{
	/*if (data->in_dir > 0 || data->out_dir > 0)
	{	
		if (dup_for_one_builtin(data) == -1)
			return (-1);
	}
	(void)list;
	if (to_fork(token) == 1)
		fork_builtin(token, data, lst_env);*/
	(void)list;
	loop_for_builtin(token, data, lst_env);
	return (0);
}

void	get_builtin_and_exec(t_list *list, t_exec *data, t_env *lst_env)
{
	while (list != NULL)
	{
		if (list->type == BUILTIN)
			one_builtin_exec(list, list->data, data, lst_env);
		list = list->next;
	}
	return ;
}
