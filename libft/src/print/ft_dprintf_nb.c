/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_nb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:21:35 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/05 14:25:29 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int n, int fd)
{
	size_t	size;

	size = 0;
	if (n == -2147483648)
		size += ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n >= 0 && n <= 9)
			size += ft_putchar_fd((n + '0'), fd);
		if (n < 0)
		{
			size += ft_putchar_fd('-', fd);
			size += ft_putnbr_fd((n *(-1)), fd);
		}
		if (n > 9)
		{
			size += ft_putnbr_fd(n / 10, fd);
			size += ft_putnbr_fd(n % 10, fd);
		}
	}
	return (size);
}

size_t	ft_putnbr_base(unsigned long nbr, char *base, int fd)
{
	size_t				base_size;
	size_t				size;

	base_size = ft_strlen(base);
	size = 0;
	if (nbr < base_size)
		size += ft_putchar_fd(base[nbr], fd);
	else
	{
		size += ft_putnbr_base(nbr / base_size, base, fd);
		size += ft_putchar_fd(base[nbr % base_size], fd);
	}
	return (size);
}

size_t	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	size_t	size;

	size = 0;
	if (n <= 9)
	{
		size += ft_putchar_fd((n + '0'), fd);
	}
	if (n > 9)
	{
		size += ft_putnbr_unsigned_fd(n / 10, fd);
		size += ft_putnbr_unsigned_fd(n % 10, fd);
	}
	return (size);
}
