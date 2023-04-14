/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:43:04 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/14 17:09:38 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct sigaction old_action;

/*int sigaction(int signum, const struct sigaction *act,
              struct sigaction *oldact);*/

static void	sigint_handler(int sig_no)
{
	(void)sig_no;
	if (sig_no == 2)
	{
		ft_dprintf(1, "\n");
		ft_dprintf(1, "doublechoc->");
	}
	
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
		struct sigaction action;
    	memset(&action, 0, sizeof(action));
    	action.sa_handler = &sigint_handler;
   	 	sigaction(SIGINT, &action, &old_action);
		line = readline(prompt_name);
		if (!line)
		{
			free(line);
			exit (1);
		}
		if (line)
			add_history(line);
		if (ft_strcmp(line, "exit") == 0)
			in_shell = 1;
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
