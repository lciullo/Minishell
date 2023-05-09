/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/09 11:02:32 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	sort_token_and_builtin(char **token, t_exec *data, char **env)
{
	if (data->nb_cmds == 1 && is_builtin(token))
		one_builtin_exec(token, data, env);
	else if (data->nb_cmds > 1)
	{
		if (is_builtin(token))
			loop_for_builtin(token, data, env);
	}
	return (0);
}

static int	loop_for_token(t_list *lst, t_exec	*data, char **env)
{
	t_list	*copy;

	copy = lst;
	while (copy != NULL)
	{
		if (copy->type == 1)
			sort_token_and_builtin(copy->data, data, env);
		copy = copy->next;
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
	list_print(lst);
	//delimiter = "stop";
	init_struct(data);
	loop_for_infile(&lst, data);
	loop_for_outfile(&lst, data);
	//loop_for_heredoc(&lst, delimiter);
	loop_for_token(lst, data, env);
}
