
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

//ft_strcmp(line, "exit") == 0

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
<<<<<<< HEAD
<<<<<<< HEAD
		parsing(line);
		(void)env;
		//execution(line, env, &data);
=======
		//parsing(&line);
		execution(line, env, &data);
>>>>>>> d6e367b032a70a3e5d1dccd1eb19d9fd8e74d3f9
=======
		parsing(&line);
		execution(line, env, &data);
>>>>>>> 6aa4cafd8ed0613cae9872319bc5ee979fa2a383
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
