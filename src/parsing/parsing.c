
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
	printf("nbr_pipe : %d\nnbr_quote : %d\nnbr_here_doc : %d\nnbr_append : %d\nnbr_input : %d\nnbr_output : %d\nnbr_redir : %d\n", parsing.nbr_pipe, parsing.nbr_quote, parsing.nbr_here_doc, parsing.nbr_append, parsing.nbr_input, parsing.nbr_output, parsing.nbr_redir);
	printf("%s\n", line);
	new_line = replace_space(line, &parsing);
	new_line = add_space(line, &parsing);
	printf("\n%s\n\n", new_line);
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

void	list_2(int	*start, int *end, char **tab_line)
{
	int malloc_size;
	//char **token;

	malloc_size = 0;
	if (tab_line[*end] == NULL)
	{
		*start = -1;
		return ;
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
	printf("malloc_size : %d | start : %d | end : %d\n", malloc_size, *start, *end);
	//token = malloc(sizeof(char *) * (malloc_size + 1));
	
}

void	create_list(char *line, t_parsing *parsing)
{
	char	**tab_line;
	int		start;
	int		end;

	start = 0;
	end = 0;
	(void) parsing;
	tab_line = ft_split(line, ' ');
	if (!tab_line)
		return ; 
	change_tab(tab_line);
	print_tab(tab_line);
	while (start != -1)
	{
		start = end;
		list_2(&start, &end, tab_line);
	}
}

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append		