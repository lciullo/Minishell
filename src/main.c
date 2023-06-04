#include "minishell.h"

static void	loop_of_prompt(char **env, char *prompt_name, t_exec *data);
static void	control_c_realod_prompt(int signal);
static void	display_new_line(int signal);
static void	core_of_program(char *line, char **env, t_exec *data);

int	main(int ac, char **av, char **env)
{
	char	*prompt_name;
	t_exec	data;

	(void)ac;
	(void)av;
	data.end = 0;
	prompt_name = "doublechoc-> ";
	loop_of_prompt(env, prompt_name, &data);
	return (0);
}

static	void	loop_of_prompt(char **env, char *prompt_name, t_exec *data)
{
	char	*line;

	while (1)
	{
		if (data->end == 1)
		{
			ft_dprintf(1, "exit\n");
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
		core_of_program(line, env, data);
	}
}

static void	core_of_program(char	*line, char **env, t_exec *data)
{
	t_list		*list;
	t_env		*lst;
	t_data		data_parsing;

	list = NULL;
	lst = NULL;
	if (ft_isascii(line) == 0)
		exit(1);
	lst = creat_env(env);
	//list_print_env(lst);
	list = parsing(line, &data_parsing, &lst);
	if (list == NULL)
		return ;
	//print_list(list);
	if (execution(list, env, &data_parsing, data, lst) == -1)
		perror("execution issue");
	free(line);
	ft_lstclear_env(&lst, free);
	ft_lstclear(&list, free);
}

static void	control_c_realod_prompt(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

static void	display_new_line(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
}
