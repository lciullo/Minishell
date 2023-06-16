/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:05:20 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/15 15:19:28 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	start_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\n')
		i++;
	return (i);
}

int	get_valid_res(char *str, int *nb)
{
	long	index;
	long	res;
	size_t	i;

	res = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*nb = -1;
		i++;
	}
	while (str[i] != ' ' && str[i])
	{
		index = 0;
		while ("0123456789"[index] != str[i] && index < 10)
			index++;
		if (index == 10 || (res * 10 + index) * *nb / 10 != res * *nb)
			return (-1);
		res = res * 10 + index;
		i++;
	}
	*nb *= res;
	return (2);
}

int	ft_atoi_exit(char *str, int *nb)
{
	size_t	i;

	i = start_str(str);
	*nb = 1;
	if (str[i] == 0)
		return (-1);
	return (get_valid_res(&str[i], nb));
}
