
#include "minishell.h"

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

static	void	loop_of_prompt(char **env)
{
	char	*prompt_name;
	char	*line;
	t_exec	data;

	(void)env;
	(void)data;
	data.end = 0;
	prompt_name = "doublechoc-> ";
	while (1)
	{
		if (data.end == 1)
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
		parsing(line);
		(void)env;
		execution(line, env, &data);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	loop_of_prompt(env);
	return (0);
}
