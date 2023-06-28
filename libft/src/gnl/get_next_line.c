/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:57:57 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/18 16:03:27 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "\0";
	char		*line;
	int			end_file;

	end_file = 1;
	line = read_the_line(buffer, &end_file, fd);
	clean_buf(buffer, &end_file);
	return (line);
}

char	*read_the_line(char *buffer, int *end_file, int fd)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	if (buffer[0] == '\0')
	{
		*end_file = read(fd, buffer, BUFFER_SIZE);
		if (*end_file < 0)
		{
			buffer[0] = '\0';
			return (NULL);
		}
		buffer[*end_file] = '\0';
		if (*end_file <= 0)
			return (line);
	}
	line = first_read(buffer, &i);
	while (buffer[i] != '\n' && *end_file > 0)
	{
		if (buffer[i++] == '\0' && *end_file > 0)
			line = gnl_join(line, next_line(buffer, end_file, &i, fd));
	}
	return (line);
}

char	*next_line(char *buffer, int *end_file, int *i, int fd)
{
	char	*continue_line;

	*i = 0;
	*end_file = read(fd, buffer, BUFFER_SIZE);
	if (*end_file < 0)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	buffer[*end_file] = '\0';
	continue_line = malloc(sizeof(char) * (next_line_len(buffer) + 2));
	if (!continue_line)
		return (NULL);
	while (buffer[*i] != '\n')
	{
		continue_line[*i] = buffer[*i];
		if (buffer[*i] == '\0')
			return (continue_line);
		*i = *i + 1;
	}
	continue_line[*i] = '\n';
	*i = *i + 1;
	continue_line[*i] = '\0';
	*i = *i - 1;
	return (continue_line);
}

void	clean_buf(char *buffer, int *end_file)
{
	int	i;

	i = 0;
	if (*end_file <= 0)
		return ;
	while (buffer[i] != '\n')
	{
		i++;
	}
	if (i + 1 == BUFFER_SIZE)
		buffer[0] = '\0';
	else
		ft_memmove(buffer, buffer + i + 1, ft_strlen(buffer + i + 1));
}

char	*first_read(char *buffer, int *i)
{
	char	*line;
	int		len_line;

	len_line = next_line_len(buffer);
	line = malloc(sizeof(char) * (len_line + 2));
	if (!line)
		return (NULL);
	while (buffer[*i] != '\n')
	{
		line[*i] = buffer[*i];
		if (buffer[*i] == '\0')
			return (line);
		*i = *i + 1;
	}
	line[*i] = '\n';
	*i = *i + 1;
	line[*i] = '\0';
	*i = *i - 1;
	return (line);
}
