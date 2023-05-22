/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:07:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/22 13:01:21 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_for_builtin(char **token, t_exec *data, t_env *lst_env)
{
	if (!token[0])
		return ;
	if (ft_strcmp(token[0], "echo") == 0)
		implement_echo(token);
	else if (ft_strcmp(token[0], "cd") == 0)
		implement_cd(token);
	else if (ft_strcmp(token[0], "pwd") == 0)
		implement_pwd(token);
	else if (ft_strcmp(token[0], "exit") == 0)
		implement_exit(token, data);
	else if (ft_strcmp(token[0], "env") == 0)
		implement_env(lst_env);
}

int	is_builtin(char **token)
{
	if (!token[0])
		return (0);
	if (ft_strcmp(token[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(token[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(token[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(token[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(token[0], "env") == 0)
		return (1);
	return (0);
}
