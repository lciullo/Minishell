/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:03:58 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/15 15:55:29 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*create_node(int *start, int *end, char **tab_line);
static int		find_malloc_size(char **tab, int *end, int start);
static int		fill_tab(char **tab_line, char **token, int *start, int *end);
static void		del_delimiteur(t_list **list);

t_list	*create_list(t_data *data, t_env *env, char **tab_line)
{
	int		start;
	int		end;
	t_list	*list;
	t_list	*new;

	start = 0;
	end = 0;
	list = NULL;
	while (start != -1)
	{
		if (tab_line[end] == NULL)
		{
			start = -1;
			break ;
		}
		start = end;
		new = create_node(&start, &end, tab_line);
		if (!(new))
		 	return (NULL);
		ft_lstadd_back(&list, new);
	}
	change_list(&list);
	if (should_we_expand(&list, env) == FAILURE)
		return (free_array(tab_line), NULL);
	parse_line_for_quote(&list);
	reput_quote(&list);
	free_array(tab_line);
	if ((data->nbr_pipe + data->nbr_redir) != 0)
		del_delimiteur(&list);
	return (list);
}

static t_list	*create_node(int *start, int *end, char **tab_line)
{
	char	**token;
	t_list	*new;

	token = malloc(sizeof(char *) * \
	(find_malloc_size(tab_line, end, *start) + 1));
	if (!token)
		return (free_array(tab_line), NULL);
	if (fill_tab(tab_line, token, start, end) == FAILURE)
		return (NULL);
	new = ft_lstnew(token, -1);
	if (!new)
		return (free_array(token), free_array(tab_line), NULL);
	return (new);
}

static int	find_malloc_size(char **tab, int *end, int start)
{
	int	malloc_size;

	malloc_size = 0;
	while (tab[*end])
	{
		if ((tab[*end][0] == '<' || tab[*end][0] == '>' \
		|| tab[*end][0] == '|') || (*end != 0 && tab[*end - 1] \
		&& (tab[*end - 1][0] == '<' || tab[*end - 1][0] == '>')))
		{
			*end = *end + 1;
			malloc_size = 1;
			break ;
		}
		else if (tab[*end + 1] && (tab[*end + 1][0] == '<' \
		|| tab[*end + 1][0] == '>' || tab[*end + 1][0] == '|'))
		{
			*end = *end + 1;
			malloc_size = *end - start;
			break ;
		}
		*end = *end + 1;
	}
	if (malloc_size == 0)
		malloc_size = (*end - start) + 1;
	return (malloc_size);
}

static int	fill_tab(char **tab_line, char **token, int *start, int *end)
{
	int	i;

	i = 0;
	while (*start < *end)
	{
		token[i] = ft_strdup(tab_line[*start]);
		if (!token[i])
			return (free_array(tab_line), free_array(token), FAILURE);
		*start = *start + 1;
		i++;
	}
	token[i] = NULL;
	return (SUCCESS);
}

static void	del_delimiteur(t_list **list)
{
	t_list	*copy;

	if (*list == NULL || list == NULL)
		return ;
	copy = (*list);
	if (copy->type == -1)
	{
		*list = copy->next;
		free_array(copy->data);
		free(copy);
		del_delimiteur(list);
	}
	copy = *list;
	del_delimiteur(&copy->next);
}
