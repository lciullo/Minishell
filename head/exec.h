/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:40:53 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/20 14:45:30 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/headers/libft.h"

//# ======== Struct ======== #

typedef struct s_exec
{
	int		in;
	int		out;
	int		fd[2];
	int		prev_fd;
}	t_exec;

/*typedef struct s_redirection
{
	int		in;
	int		out;
	int		check_heredoc;
	char	*limiter;
}	t_redirection;*/

void	execution(char *line, char **env);

//# ======== Temporary ======== #

void	loop_for_heredoc(t_list *lst, char *limiter);

//void	init_struct(t_pipex *data);

#endif