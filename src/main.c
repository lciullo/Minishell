#include "minishell.h"

static void	loop_of_prompt(char *prompt_name, t_exec *data, t_env *lst, char *line);
static void	control_c_realod_prompt(int signal);
static void	display_new_line(int signal);
static void	core_of_program(char *line, t_exec *data, t_env **lst);

int g_exit_status;

int	main(int ac, char **av, char **env)
{
	char		*prompt_name;
	char		*line;
	t_exec		data;
	t_env		*lst;

	(void)ac;
	(void)av;
	line = NULL;
	lst = NULL;
	lst = creat_env(env);
	if (!lst)
		perror("Issue to create env in linked list");
	g_exit_status = 0;
	data.end = 0;
	prompt_name = "\001"BLUE"\002""doublechoc-> ""\001"END"\002";
	loop_of_prompt(prompt_name, &data, lst, line);
	return (g_exit_status);
}

static	void	loop_of_prompt(char *prompt_name, t_exec *data, t_env *lst, char *line)
{
	while (1)
	{
		if (data->end == 1)
		{
			ft_dprintf(1, "exit\n");
			if (lst)
				ft_lstclear_env(&lst, free);
			break ;
		}
		signal(SIGINT, control_c_realod_prompt);
		signal(SIGQUIT, SIG_IGN);
		line = readline(prompt_name);
		signal(SIGINT, display_new_line);
		if (!line)
		{
			ft_dprintf(2, "exit\n");
			free(line);
			exit (1);
		}
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
	if (execution(list, &data_parsing, data, lst) == FAILURE)
		perror("execution issue");
	if (list != NULL)
		ft_lstclear(&list, free);
}

static void	control_c_realod_prompt(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

static void	display_new_line(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
}
