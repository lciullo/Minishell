#include "minishell.h"

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

int	implement_echo(char **cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	g_exit_status = 0;
	if (!cmd[1] && cmd[0])
	{
		ft_dprintf(1, "\n");
		return (0);
	}
	if (cmd[1])
		option = parse_option(cmd[1]);
	while (cmd && cmd[i] != NULL && parse_option(cmd[i]) == 0)
		i++;
	while (cmd && cmd[i] != NULL)
	{
		ft_dprintf(1, "%s", cmd[i]);
		if (cmd[i + 1])
			ft_dprintf(1, " ");
		i++;
	}
	if (option)
		ft_dprintf(1, "\n");
	return (0);
}
