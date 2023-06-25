#include "minishell.h"

static int	count_dash(char *arg);
static int	is_valid_option(char *arg);
static int	parse_option(char *arg);
static void	write_in_echo(char **cmd, int i, int option);

void	implement_echo(char **cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	g_exit_status = 0;
	if (!cmd[1] && cmd[0])
	{
		write(1, "\n", 1);
		return ;
	}
	if (cmd[1])
		option = parse_option(cmd[1]);
	while (cmd && cmd[i] != NULL && parse_option(cmd[i]) == 0)
		i++;
	write_in_echo(cmd, i, option);
	return ;
}

static	int	parse_option(char *arg)
{
	int		dash;

	dash = count_dash(arg);
	if (dash != 1)
		return (1);
	if (is_valid_option(arg) == 1)
		return (1);
	return (0);
}

static	int	count_dash(char *arg)
{
	int	i;
	int	dash;

	i = 0;
	dash = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '-')
			dash++;
		i++;
	}
	return (dash);
}

static	int	is_valid_option(char *arg)
{
	size_t	i;

	i = 0;
	while (arg && arg[i] != 0 && (arg[i] == '-' || arg[i] == 'n'))
		i++;
	if (ft_strlen(arg) == i)
		return (0);
	return (1);
}

static void	write_in_echo(char **cmd, int i, int option)
{
	while (cmd && cmd[i] != NULL)
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (option)
		write(1, "\n", 1);
}
