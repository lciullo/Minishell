/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:40:57 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/09 10:51:46 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	dup_for_one_builtin(t_exec *data)
{
	if (data->infile != 0)
	{
		dup2(data->infile, STDIN_FILENO);
	}
	if (data->outfile != 0)
	{
		dup2(data->outfile, STDOUT_FILENO);
	}
	return (0);
}

int	one_builtin_exec(char **token, t_exec *data, char **env)
{
	int	pid;

	pid = 0;
	pid = fork();
	if (pid == 0)
	{
		dup_for_one_builtin(data);
		loop_for_builtin(token, data, env);
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
