/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:43:04 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/14 11:39:09 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*prompt;
	char	*line;
	int		done;

	done = 0;
	prompt = "doublechoc->";
	while (done == 0)
	{
		line = readline(prompt);
		if (!line)
			exit (1);
		if (line)
			add_history(line);
		if (strcmp(line, "exit") == 0)
			done = 1;
	}
	free(line);
	return 0;
}
