/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:54:30 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 16:37:19 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "exec.h"
# include <sys/wait.h>
# include "../libft/headers/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>

# define END "\033[0m"
# define GREY "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"

# define END "\033[0m"
# define BOLD "\033[1m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define DEL_LINE "\033[2K\r"

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

#endif