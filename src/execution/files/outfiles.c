/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:32:29 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 15:44:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	is_outfile_open(t_exec *data)
{
	if (data->outfile > 2)
		close(data->outfile);
}

static	void	manage_outfile(char *outfile, t_exec *data)
{

	is_outfile_open(data);
	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		perror("open outfile");
}

/*static void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_dprintf(1, "array[i] %s\n", array[i]);
		i++;
	}
}*/

void	loop_for_outfile(t_list **lst, t_exec *data)
{
	int		i;
	t_list	*copy;

	i = 0;
	copy = *lst;
	while (copy != NULL)
	{
		//print_array(copy->data);
		i = 0;
		while (copy->data[i] != NULL)
		{
			if (ft_strcmp(copy->data[i], ">") == 0)
			{
				i++;
				ft_dprintf(1, "%s\n", copy->data[i]);
				manage_outfile(copy->data[i], data);
				break ;
			}
			else
				i++;
		}
		copy = copy->next;
	}
}
