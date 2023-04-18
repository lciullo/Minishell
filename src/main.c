
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
	int		in_shell;

	in_shell = 0;
	prompt_name = "doublechoc->";
	while (in_shell == 0)
	{
		signal(SIGINT, control_c_realod_prompt);
		signal(SIGQUIT, SIG_IGN);
		line = readline(prompt_name);
		signal(SIGINT, display_new_line);
		if (!line)
		{
			ft_dprintf(1, "exit\n"); 
			free(line);
			exit (1); //builtine exit 
		}
		if (line[0])
			add_history(line);
		if (ft_strcmp(line, "exit") == 0)
			in_shell = 1;
		printf("line: %s\n", line);
		parsing(&line);
		execution(line, env);
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
