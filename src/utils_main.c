/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:28:39 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 22:47:04 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	control_c_realod_prompt(int signal);
static void	display_new_line(int signal);

void	empty_line_prompt(char *line, t_env *lst)
{
	ft_dprintf(2, "exit\n");
	free(line);
	if (lst)
		ft_lstclear_env(&lst, free);
	exit (g_exit_status);
}

char	*get_line_and_init_signal(char *prompt_name)
{
	char	*line;

	signal(SIGINT, control_c_realod_prompt);
	signal(SIGQUIT, SIG_IGN);
	line = readline(prompt_name);
	signal(SIGINT, display_new_line);
	free(prompt_name);
	return (line);
}

static void	control_c_realod_prompt(int signal)
{
	g_exit_status = 130;
	(void)signal;
	ft_dprintf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

static void	display_new_line(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
}
