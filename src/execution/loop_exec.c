/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/10 09:57:29 by lciullo          ###   ########.fr       */
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

static	int	get_next_pipe(t_list **lst)
{
	int		index;

	index = 0;
	while (*lst != NULL && (*lst)->type != 3)
	{
		index++;
		*lst = (*lst)->next;
	}
	return (index);
}

static	t_list	*lst_increment(t_list *lst, int index)
{
	int	i;

	i = 0;
	while (lst != NULL && i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}


static int	loop_pipe_by_pipe(t_list *lst, t_exec	*data, char **env)
{
	int	index;

	index = 0;
	(void)env;
	(void)data;
	while (lst != NULL)
	{
		//loop_for_infile(lst, data);
		//loop_for_outfile(lst, data);
		//in_exec_print_list(lst);
		in_exec_print_list(lst);
		index = get_next_pipe(&lst);
		lst = lst_increment(lst, index);
	}
	return (0);
}

void	execution(char *line, char **env, t_exec *data)
{
	t_list			*lst;
	//char			*delimiter;

	(void)line;
	lst = NULL;
	tmp_lst(&lst);
	//delimiter = "stop";
	init_struct(data);
	//loop_for_heredoc(&lst, delimiter);
	loop_pipe_by_pipe(lst, data, env);
}
