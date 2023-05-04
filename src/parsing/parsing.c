/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/04 15:46:58 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_list(char *line, t_parsing *parsing);

t_list	*parsing(char *line)
{
	t_parsing	parsing;
	char		*new_line;

	(void)line;
	init_structure(&parsing);
	count_separator(line, &parsing);
	new_line = replace_space(line, &parsing);
	new_line = add_space(line, &parsing);
	return (create_list(new_line, &parsing));
}

char	*delete_quote(char *line, int j)
{
	char	*new_line;
	int		i;
	int		k;

	new_line = malloc(sizeof(char) * (j - 2 + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	k = 1;
	while (k < j - 1)
	{		
		new_line[i] = line[k];
		i++;
		k++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	change_tab(char **tab_line)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (tab_line[i])
	{
		if (tab_line[i][0] == 34 || tab_line[i][0] == 39)
		{
			j = 0;
			quote = tab_line[i][0];
			while (tab_line[i][j])
			{
				if (tab_line[i][j] == -1)
					tab_line[i][j] = ' ';
				j++;
			}
			if (tab_line[i][j - 1] == quote)
				tab_line[i] = delete_quote(tab_line[i], j);
		}
		i++;
	}
}

t_list	*list_2(int	*start, int *end, char **tab_line)
{
	int		malloc_size;
	char	**token;
	int		i;
	t_list	*new;

	malloc_size = 0;
	i = 0;
	if (tab_line[*end] == NULL)
	{
		*start = -1;
		return (NULL);
	}
	while (tab_line[*end])
	{
		if ((tab_line[*end][0] == '<' || tab_line[*end][0] == '>' \
		|| tab_line[*end][0] == '|'))
		{
			*end = *end + 1;
			malloc_size = 1;
			break ;
		}
		else if (*end != 0 && tab_line[*end - 1] && \
		(tab_line[*end - 1][0] == '<' || tab_line[*end - 1][0] == '>'))
		{
			*end = *end + 1;
			malloc_size = 1;
			break ;
		}
		else if (tab_line[*end + 1] && (tab_line[*end + 1][0] == '<' \
		|| tab_line[*end + 1][0] == '>' || tab_line[*end + 1][0] == '|'))
		{
			*end = *end + 1;
			malloc_size = *end - *start;
			break ;
		}
		*end = *end + 1;
	}
	token = malloc(sizeof(char *) * (malloc_size + 1));
	if (!token)
		return (NULL);
	while (*start < *end)
	{
		token[i] = ft_strdup(tab_line[*start]);
		if (!token)
			return (NULL);
		*start = *start + 1;
		i++;
	}
	token[i] = NULL;
	new = ft_lstnew(token, -1);
	if (!new)
		return (NULL);
	return (new);
}

void	print_list(t_list	*a)
{
	printf(" data        | type\n");
	printf("-------------------\n");
	while (a)
	{
		print_tab(a->data);
		printf("%d\n", a->type);
		if (a->next != NULL)
			printf("------------------\n");
		a = a->next;
	}
}

void	change_list(t_list **list)
{
	t_list	*temp;

	temp = (*list);
	while (temp)
	{
		if (temp->data[0][0] == '>' && temp->data[0][1] == '>')
			temp->next->type = APPEND;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '<')
			temp->next->type = HERE_DOC;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '\0')
			temp->next->type = INFILE;
		else if (temp->data[0][0] == '>' && temp->data[0][1] == '\0')
			temp->next->type = OUTFILE;
		else if (temp->type == -1 && \
		(temp->data[0][0] != '>' || temp->data[0][0] != '<'))
			temp->type = TOKEN;
		temp = temp->next;
	}
}

void	del_delimiteur(t_list **list)
{
	t_list	*copy;
	t_list	*temp;
	t_list	*del;
	int		i;

	copy = (*list);
	del = NULL;
	i = 0;
	while (copy->next)
	{
		if (i == 0 && copy->type == -1)
		{
			del = copy;
			free(del->data);
			free(del);
			(*list) = (*list)->next;
		}
		if (copy->next->type == -1)
		{
			del = copy;
			temp = copy->next->next;
			free(del->next->data);
			free(del->next);
			del->next = temp;
			copy = del;
		}
		else
			copy = copy->next;
		i++;
	}
}

t_list	*create_list(char *line, t_parsing *parsing)
{
	char	**tab_line;
	int		start;
	int		end;
	t_list	*list;
	t_list	*new;

	start = 0;
	end = 0;
	list = NULL;
	(void) parsing;
	tab_line = ft_split(line, ' ');
	if (!tab_line)
		return (NULL);
	change_tab(tab_line);
	while (start != -1)
	{
		start = end;
		new = list_2(&start, &end, tab_line);
		ft_lstadd_back(&list, new);
	}
	change_list(&list);
	del_delimiteur(&list);
	return (list);
}

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append		