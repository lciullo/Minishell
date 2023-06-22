#include "minishell.h"

t_list	*parsing(char *line, t_data *data, t_env *lst_env)
{
	t_list		*list;
	char		**tab_line;

	list = NULL;
	if (skip_ws(line) == 1)
	{
		g_exit_status = 0;
		return (NULL);
	}
	init_structure(data, lst_env, line);
	if (check_error(data) == false)
	{
		g_exit_status = 2;
		return (NULL);
	}
	tab_line = prepare_line_for_list(data);
	if (!tab_line)
		return (print_error(MALLOC_ERR), NULL);
	list = create_list(data, lst_env, tab_line);
	if (!list)
		return (print_error(MALLOC_ERR), NULL);
	return (list);
}

void	print_error(int error_code)
{
	if (error_code == MALLOC_ERR)
	{
		g_exit_status = 1;
		ft_dprintf(2, "minishell : a malloc failed during the parsing\n");
	}
	else if (error_code == HERE_DOC_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'<<\'\n");
	else if (error_code == APPEND_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'>>\'\n");
	else if (error_code == IN_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'<\'\n");
	else if (error_code == OUT_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'>\'\n");
	else if (error_code == PIPE_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'|\'\n");
	else if (error_code == S_QUOTE_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'\'\'\n");
	else if (error_code == D_QUOTE_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'\"\'\n");
}
