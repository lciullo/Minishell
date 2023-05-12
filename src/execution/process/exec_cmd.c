/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/12 14:31:21 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_command(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == TOKEN)
			data->cmd = list->data[0];
		list = list->next;
	}
}

static char	**token(t_list *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == TOKEN)
			return (list->data);
		list = list->next;
	}
	return (NULL);
}


static void	dupe_test(t_exec *data)
{
	if (dup2(data->infile, STDIN_FILENO) == -1)
		return ;
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		return ;
}

int	execution_core(t_list *list, t_data *parsing, t_exec *data, char **env)
{
	int		pid;
	int		fd[2];
	(void)parsing;
	(void)env;

	pid = 0;
	fd[0] = 0;
	fd[1] = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (loop_for_infile(list, data) == -1)
			return (-1);
		loop_for_outfile(list, data);
		dupe_test(data);
		get_command(list, data);
		data->cmd_with_path = check_cmd_acess(data->env_path, data->cmd);
		if (!data->cmd_with_path)
			return (-1);
		execve(data->cmd_with_path, token(list), env);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
