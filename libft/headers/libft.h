/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:01:44 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/05 14:31:19 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>

# include <unistd.h>

# include <stdarg.h>

# include <fcntl.h>

# include <stdint.h>

# define HEXA_LOW "0123456789abcdef"

# define HEXA_UP "0123456789ABCDEF"

//# ====================== LIBFT ====================== #

//# ============ STRING ============ #

//# ---- libft string functions ---- #

size_t			ft_strlen(const char *str);

char			*ft_strdup(const char *src);

char			*ft_substr(const char *s, unsigned int start, size_t len);

char			*ft_strjoin(char *s1, char *s2);

int				ft_strncmp(char *s1, char *s2, size_t n);

char			*ft_strchr(char *str, int c);

char			**ft_split(char const *s, char c);

size_t			nb_words(char const *s, char c);

char			*ft_itoa(int n);

void			*ft_calloc(size_t nb_elements, size_t size);

void			ft_bzero(void *s, size_t n);

char			*ft_strnstr(const char *str, const char *search, size_t n);

//# ---- free functions ---- #

void			free_array(char **arr);

void			secure_free_array(char **arr, size_t line);

//# ============ PRINT STDERR ============ #

//# ---- drpintf --- #

int				ft_dprintf(int fd, const char *str, ...);

size_t			ft_putchar_fd(int c, int fd);

size_t			ft_putstr_fd(char *s, int fd);

size_t			ft_strlen(const char *str);

size_t			ft_putnbr_fd(int n, int fd);

size_t			ft_putnbr_base(unsigned long nbr, char *base, int fd);

size_t			ft_putnbr_unsigned_fd(unsigned int n, int fd);

#endif
