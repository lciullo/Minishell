#include "minishell.h"

static void	get_nbr_pipe(char *line, t_data *data);

char	**prepare_line_for_list(t_data *data)
{
	char	*new_line;
	char	**tab_line;

	new_line = add_space(data->line, 0, (data->len_line + \
	((data->nbr_pipe * 2 + data->nbr_redir * 2)) + 1));
	if (!(new_line))
		return (NULL);
	replace_space(new_line, 0);
	get_nbr_pipe(new_line, data);
	tab_line = ft_split_parsing(new_line);
	free(new_line);
	if (!tab_line)
		return (NULL);
	tab_line = change_order(tab_line, data);
	if (!(tab_line))
		return (NULL);
	change_tab(tab_line, 1);
	return (tab_line);
}

static void	get_nbr_pipe(char *line, t_data *data)
{
	int	i;

	i = 0;
	data->nbr_pipe = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] && line[i] == '|')
			data->nbr_pipe++;
		if (line[i])
			i++;
	}
}
