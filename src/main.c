/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:19:35 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 22:30:06 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_of_prompt(char *prompt_name, t_exec *data, \
			t_env *lst, char *line);
static void	core_of_program(char *line, t_exec *data, t_env **lst);

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_exec		data;
	t_env		*lst;
	char		*prompt_name;

	(void)ac;
	(void)av;
	line = NULL;
	lst = NULL;
	prompt_name = NULL;
	lst = creat_env(env);
	if (!lst)
		perror("Issue to create env in linked list");
	g_exit_status = 0;
	data.end = 0;
	loop_of_prompt(prompt_name, &data, lst, line);
	return (g_exit_status);
}

static	void	loop_of_prompt(char *prompt_name, t_exec *data, \
				t_env *lst, char *line)
{
	while (1)
	{
		prompt_name = ft_strdup("doublechoc-> ");
		if (!prompt_name)
		{
			print_error(MALLOC_ERR_MAIN);
			break ;
		}
		if (data->end == 1)
		{
			ft_dprintf(1, "exit\n");
			free(prompt_name);
			if (lst)
				ft_lstclear_env(&lst, free);
			break ;
		}
		line = get_line_and_init_signal(prompt_name);
		if (!line)
			empty_line_prompt(line, lst);
		if (line[0])
			add_history(line);
		core_of_program(line, data, &lst);
	}
}

static void	core_of_program(char *line, t_exec *data, t_env **lst)
{
	t_list		*list;
	t_data		data_parsing;

	list = NULL;
	if (ft_isascii(line) == 0)
	{
		if (lst)
			ft_lstclear_env(lst, free);
		free(line);
		exit(1);
	}
	list = parsing(line, &data_parsing, *lst);
	free(line);
	if (list == NULL)
		return ;
	execution(list, &data_parsing, data, lst);
	if (list != NULL)
		ft_lstclear(&data->head, free);
}
