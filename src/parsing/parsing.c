
#include "minishell.h"
#include <stdio.h>

void	create_list(char *line, t_parsing *parsing);

int	parsing(char *line)
{
	
	t_parsing	parsing;
	char *new_line;
	
	(void)line;
	init_structure(&parsing);
	count_separator(line, &parsing);
	//printf("nbr_pipe : %d\nnbr_quote : %d\nnbr_here_doc : %d\nnbr_append : %d\nnbr_input : %d\nnbr_output : %d\nnbr_redir : %d\n", parsing.nbr_pipe, parsing.nbr_quote, parsing.nbr_here_doc, parsing.nbr_append, parsing.nbr_input, parsing.nbr_output, parsing.nbr_redir);
	//printf("%s\n", line);
	new_line = replace_space(line, &parsing);
	new_line = add_space(line, &parsing);
	//printf("\n%s\n\n", new_line);
	create_list(new_line, &parsing);
	return (0);
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
	while(tab_line[i])
	{
		if(tab_line[i][0] == 34 || tab_line[i][0] == 39)
		{
			j = 0;
			quote = tab_line[i][0];
			while(tab_line[i][j])
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
	int malloc_size;
	char **token;
	int	i;
	t_list	*new;

	malloc_size = 0;
	i = 0;
	if (tab_line[*end] == NULL)
	{
		*start = -1;
		return NULL;
	}
	while (tab_line[*end])
	{
		if ((tab_line[*end][0] == '<' || tab_line[*end][0] == '>' || tab_line[*end][0] == '|'))
		{
			*end = *end + 1;
			malloc_size = 1;
			break ;
		}
		else if (*end != 0 && tab_line[*end - 1] && (tab_line[*end - 1][0] == '<' || tab_line[*end - 1][0] == '>'))
		{
			*end = *end + 1;
			malloc_size = 1;
			break ;
		}
		else if (tab_line[*end + 1] && (tab_line[*end + 1][0] == '<' || tab_line[*end + 1][0] == '>' || tab_line[*end + 1][0] == '|'))
		{
			*end = *end + 1;
			malloc_size = *end - *start;
			break ;
		}
		*end = *end + 1;
	}
	//printf("malloc_size : %d | start : %d | end : %d\n", malloc_size, *start, *end);
	token = malloc(sizeof(char *) * (malloc_size + 1));
	if (!token)
		return NULL;
	while (*start < *end)
	{
		token[i] = ft_strdup(tab_line[*start]);
		if (!token)
			return NULL;
		//printf("token[%d] = %s\n", i, token[i]);
		*start = *start + 1;
		i++;
	}
	token[i] = NULL;
	new = ft_lstnew(token, 0);
	if (!new)
		return NULL;
	return (new);
}
void	print_list(t_list	*a)
{
	printf(" data        | type\n");
	printf("-------------------\n");
	while (a)
	{
		print_tab(a->data);
		printf(" | ");
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
	while (temp->next)
	{
		if (temp->data[0][0] == '>' && temp->data[0][1] == '>')
			temp->next->type = APPEND;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '<')
			temp->next->type = HERE_DOC;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '\0')
			temp->next->type = INFILE;
		else if (temp->data[0][0] == '>' && temp->data[0][1] == '\0')
			temp->next->type = OUTFILE;
		temp = temp->next;
	}
	*list = temp;
}

void	create_list(char *line, t_parsing *parsing)
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
		return ; 
	change_tab(tab_line);
	//print_tab(tab_line);
	while (start != -1)
	{
		start = end;
		new = list_2(&start, &end, tab_line);
		ft_lstadd_back(&list, new);
	}
	change_list(&list);
	print_list(list);
}

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append		