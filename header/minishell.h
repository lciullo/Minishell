/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:54:30 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/28 13:15:53 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include "../libft/headers/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
#include "parsing.h"
#include "exec.h"

# define END "\033[0m"
# define BLUE "\033[1;34m"

extern int	g_exit_status;

enum {
	FAILURE = -1,
	BREAK = -6,
	SUCCESS = 2,
	ONLY_HEREDOC = -2,
	PLUS = 3,
	EQUAL = 4,
	NO_EQUAL = 5,
};

/* ---- utils_main.c ----*/
void	empty_line_prompt(char *line, t_env *lst);
char	*get_line_and_init_signal(char *prompt_name);

#endif