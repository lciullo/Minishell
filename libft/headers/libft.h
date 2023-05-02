/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:01:44 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/02 12:32:59 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define HEXA_LOW "0123456789abcdef"
# define HEXA_UP "0123456789ABCDEF"

typedef struct s_list
{
	char			**data;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_lst_env
{
	char				*variable;
	char				*value;
	int					equal;
	struct s_lst_env	*next;
}	t_lst_env;

//# ====================== LIBFT ====================== #

//# ============ LIST ============ #

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_back_env(t_lst_env **lst, t_lst_env *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_lst_env		*ft_lstlast_env(t_lst_env *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
t_list			*ft_lstnew(char **token, int type);
t_lst_env		*ft_lstnew_env(char *variable, char *value);
int				ft_lstsize(t_list *lst);
void			list_print(t_list *lst);
void			list_print_env(t_lst_env *lst);
char			*ft_strcpy(char *dest, const char *src);
//# ============ LIBRARY ============ #

long			ft_atoi_long(char *str);
int				ft_atoi(const char *str);
int				ft_isalnum(int c);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nb_elements, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_strchr(char *str, int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(const char *src);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin_heredoc(char *s1, char *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t			ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(char *s1, char *s2, size_t n);
char			*ft_strnstr(const char *str, const char *search, size_t n);
char			*ft_strndup(char *dest, char *src, unsigned int n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(const char *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
size_t			nb_words(char const *s, char c);

//# ---- free functions ---- #

void			free_array(char **arr);
void			secure_free_array(char **arr, size_t line);

//# ============ PRINT STDERR ============ #

//# ---- drpintf --- #

int				ft_dprintf(int fd, const char *str, ...);
size_t			ft_putchar_fd(int c, int fd);
size_t			ft_putstr_fd(char *s, int fd);
size_t			ft_putnbr_fd(int n, int fd);
size_t			ft_putnbr_base(unsigned long nbr, char *base, int fd);
void			ft_putendl_fd(char *s, int fd);
size_t			ft_putnbr_unsigned_fd(unsigned int n, int fd);

//# ============ GET NEXT LINE ============ #

char			*get_next_line(int fd);
unsigned int	next_line_len(char *buffer);
char			*read_the_line(char *buffer, int *end_file, int fd);
char			*next_line(char *buffer, int *end_file, int *i, int fd);
void			clean_buf(char *buffer, int *end_file);
char			*first_read(char *buffer, int *i);
char			*gnl_join(char *s1, char *s2);

#endif
