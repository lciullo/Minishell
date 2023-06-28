/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:24:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/05 14:27:58 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	base_conv(va_list list, char c, int fd)
{
	ssize_t	size;

	size = 0;
	if (c == 'c')
		return (ft_putchar_fd(va_arg(list, int), fd));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(list, char *), fd));
	else if (c == 'p')
	{
		size = ft_putstr_fd("0x", fd);
		size += (ft_putnbr_base((size_t)va_arg(list, long long int), \
			HEXA_LOW, fd));
	}
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(list, int), fd));
	else if (c == 'u')
		return (ft_putnbr_unsigned_fd(va_arg(list, unsigned int), fd));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(list, unsigned int), HEXA_LOW, fd));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(list, unsigned int), HEXA_UP, fd));
	else if (c == '%')
		return (ft_putchar_fd('%', fd));
	return (size);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	list;
	size_t	i;
	size_t	size;

	va_start(list, str);
	i = 0;
	size = 0;
	if (write (fd, 0, 0))
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
			size += base_conv(list, str[++i], fd);
		else
			size += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(list);
	return (size);
}
