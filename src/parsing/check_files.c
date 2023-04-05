/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:25:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/17 15:51:57 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(char *infile, char *outfile, t_pipex *data)
{
	data->infile = open(infile, O_RDONLY);
	if (data->infile < 0)
	{
		data->check_infile = 1;
		perror("open");
	}
	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile < 0)
	{
		data->check_outfile = 1;
		perror("open");
	}
	return (1);
}
