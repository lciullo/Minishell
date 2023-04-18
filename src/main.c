/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:43:04 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/18 13:25:05 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	control_c_realod_prompt(int signal)
{
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

static	void	loop_of_prompt(void)
{
	char	*prompt_name;
	char	*line;
	int		in_shell;

	in_shell = 0;
	prompt_name = "doublechoc->";
	while (in_shell == 0)
	{
		signal(SIGINT, control_c_realod_prompt);
		signal(SIGQUIT, SIG_IGN);
		line = readline(prompt_name);
		signal(SIGINT, display_new_line);
		if (!line)
		{
			ft_dprintf(1, "exit\n"); 
			free(line);
			exit (1); //builtine exit 
		}
		if (line[0])
			add_history(line);
		if (ft_strcmp(line, "exit") == 0)
			in_shell = 1;
		printf("line: %s\n", line);
		parsing(&line);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	loop_of_prompt();
	return (0);
}
