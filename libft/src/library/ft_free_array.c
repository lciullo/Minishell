/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:56:52 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/13 15:51:58 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **arr)
{
	size_t	row;

	row = 0;
	while (arr[row])
	{
		free(arr[row]);
		row++;
	}
	free(arr);
	arr = NULL;
	return ;
}

void	secure_free_array(char **arr, size_t line)
{
	size_t	row;

	row = 0;
	while (row < line)
	{
		free(arr[row]);
		row++;
	}
	if (line != 0)
		free(arr);
	return ;
}
