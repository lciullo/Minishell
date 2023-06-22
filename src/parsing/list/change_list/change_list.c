#include "minishell.h"

static void	change_type(t_list **list);
static void	get_type_quote_here_doc(t_list **list);
static void	is_it_empty(t_list **list);
static int	parse_line_for_quote(t_list **list);

int	change_list(t_list **list, t_env *env, t_data *data, char **tab_line)
{
	t_list	*temp;

	temp = NULL;
	change_type(list);
	if (should_we_expand(list, env) == FAILURE)
		return (free_array(tab_line), FAILURE);
	is_it_empty(list);
	if (parse_line_for_quote(list) == FAILURE)
		return (ft_lstclear(list, free), free_array(tab_line), FAILURE);
	temp = (*list);
	while (temp)
	{
		change_tab(temp->data, 2);
		temp = temp->next;
	}
	free_array(tab_line);
	if ((data->nbr_pipe + data->nbr_redir) != 0)
		del_delimiteur(list);
	return (SUCCESS);
}

static void	change_type(t_list **list)
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
		else if (temp->data[0][0] == '|')
			temp->type = PIPE;
		else if (temp->type == -1 && is_builtins(temp->data[0]) == true)
			temp->type = BUILTIN;
		else if (temp->type == -1 && \
		(temp->data[0][0] != '>' || temp->data[0][0] != '<'))
			temp->type = TOKEN;
		temp = temp->next;
	}
	get_type_quote_here_doc(list);
}

static void	get_type_quote_here_doc(t_list **list)
{
	t_list	*temp;
	int		i;

	temp = (*list);
	while (temp)
	{
		if (temp->type == HERE_DOC)
		{
			i = 0;
			while (temp->data[0][i])
			{
				if (temp->data[0][i] == '\'' || temp->data[0][i] == '\"')
				{
					temp->quote_here_doc = 1;
					break ;
				}
				i++;
			}
		}
		temp = temp->next;
	}
}

static void	is_it_empty(t_list **list)
{
	t_list	*temp;

	temp = (*list);
	while (temp)
	{
		if (temp->data[0][0] == '\0')
		{
			temp->empty = 0;
		}
		temp = temp->next;
	}
}

static int	parse_line_for_quote(t_list **list)
{
	t_list	*temp;
	char	*temp_str;
	int		r;

	temp = (*list);
	while (temp)
	{
		if (temp->type != PIPE)
		{
			r = 0;
			while (temp->data[r])
			{
				temp_str = temp->data[r];
				temp->data[r] = is_there_a_quote(temp->data[r]);
				if (!(temp->data[r]))
				{
					temp->data[r] = temp_str;
					return (FAILURE);
				}
				r++;
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
