/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:39:47 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 19:36:41 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parsing(char *line, t_data *data, t_env *lst_env)
{
	t_list		*list;
	char		**tab_line;

	list = NULL;
	if (skip_ws(line) == 1)
	{
		g_exit_status = 0;
		return (NULL);
	}
	init_structure(data, lst_env, line);
	if (check_error(data) == false)
	{
		g_exit_status = 2;
		return (NULL);
	}
	tab_line = prepare_line_for_list(data);
	if (!tab_line)
		return (print_error(MALLOC_ERR_PARS), NULL);
	list = create_list(data, lst_env, tab_line);
	if (!list)
		return (print_error(MALLOC_ERR_PARS), NULL);
	return (list);
}

void	print_error(int error_code)
{
	if (error_code == MALLOC_ERR_PARS)
	{
		g_exit_status = 1;
		ft_dprintf(2, "minishell : a malloc failed during the parsing\n");
	}
	else if (error_code == MALLOC_ERR_MAIN)
	{
		g_exit_status = 1;
		ft_dprintf(2, "minishell : the malloc of the prompt_name failed\n");
	}
	else if (error_code == MALLOC_ERR_EXEC)
	{
		g_exit_status = 1;
		ft_dprintf(2, "minishell : a malloc failed during the execution\n");
	}
	else if (error_code == REDIR_ERR)
		ft_dprintf(2, "minishell : syntax error near redirection\n");
	else if (error_code == PIPE_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'|\'\n");
	else if (error_code == QUOTE_ERR)
		ft_dprintf(2, "minishell : syntax error : unclosed quote\n");
}
