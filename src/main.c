/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:43:04 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/14 14:46:00 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	loop_of_prompt(void)
{
	char	*prompt_name;
	char	*line;
	int		done;

	done = 0;
	prompt_name = "doublechoc->";
	while (done == 0)
	{
		line = readline(prompt_name);
		if (!line)
		{
			free(line);
			exit (1);
		}
		if (line)
			add_history(line);
		if (ft_strcmp(line, "exit") == 0)
			done = 1;
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
