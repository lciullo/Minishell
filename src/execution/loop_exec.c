/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/10 11:12:00 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
===============
Type
===============
Infile = 0
Token = 1
Outfile = 2
Pipe = 3
*/


// static	int	sort_token_and_builtin(char **token, t_exec *data, char **env)
// {
// 	if (data->nb_cmds == 1 && is_builtin(token))
// 		one_builtin_exec(token, data, env);
// 	else if (data->nb_cmds > 1)
// 	{
// 		if (is_builtin(token))
// 			loop_for_builtin(token, data, env);
// 	}
// 	return (0);
// }

static	int	get_next_pipe(t_list **list)
{
	int		index;

	index = 0;
	while (*list != NULL && (*list)->type != PIPE)
	{
		index++;
		*list = (*list)->next;
	}
	return (index);
}

static	t_list	*list_increment(t_list *list, int index)
{
	int	i;

	i = 0;
	while (list != NULL && i < index)
	{
		list = list->next;
		i++;
	}
	return (list);
}


static int	loop_pipe_by_pipe(t_list *list, t_exec	*data, char **env)
{
	int	index;

	index = 0;
	(void)env;
	(void)data;
	while (list != NULL)
	{
		//loop_for_infile(list, data);
		//loop_for_outfile(list, data);
		//in_exec_print_list(list);
		in_exec_print_list(list);
		index = get_next_pipe(&list);
		list = list_increment(list, index);
	}
	return (0);
}

void	execution(t_list *list, char **env, t_exec *data)
{
	
	//char			*delimiter;
	//delimiter = "stop";
	init_struct(data);
	//loop_for_heredoc(&list, delimiter);
	loop_pipe_by_pipe(list, data, env);
}
