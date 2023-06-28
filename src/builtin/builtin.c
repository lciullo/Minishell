/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:07:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 23:06:28 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_for_builtin(char **token, t_exec *data, t_env **lst)
{
	if (!token[0])
		return ;
	if (ft_strcmp(token[0], "echo") == 0)
		implement_echo(token);
	else if (ft_strcmp(token[0], "cd") == 0)
		implement_cd(token, lst);
	else if (ft_strcmp(token[0], "pwd") == 0)
		implement_pwd(token);
	else if (ft_strcmp(token[0], "exit") == 0)
		implement_exit(token, data);
	else if (ft_strcmp(token[0], "env") == 0)
		implement_env(token, *lst);
	else if (ft_strcmp(token[0], "export") == 0)
		implement_export(token, lst, data);
	else if (ft_strcmp(token[0], "unset") == 0)
		implement_unset(token, lst);
}
