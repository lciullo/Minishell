
#include "minishell.h"

static int	is_valid(int c)
{
	if ((c >= '0' && c <= '9') || (c == ' ') || (c == '-' || c == '+'))
	{
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

static int	ft_is_numeric(char *nb)
{
	int	i;

	i = 0;
	while (nb[i] != '\0')
	{
		if (is_valid(nb[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	implement_exit(char **cmd, t_exec *data)
{
	int	nb;

	if (ft_strcmp(cmd[0], "exit") == 0 && !cmd[1])
	{
		data->end = 1;
		return (0);
	}
	if (((ft_atoi_exit(cmd[1], &nb) == FAILURE) || ft_is_numeric(cmd[1]) == FAILURE))
	{
		g_exit_status = 2;
		ft_dprintf(2, "exit\nminishell: exit: %s: numeric argument is required\n",
			cmd[1]);
		data->end = 1;
		return (FAILURE);
	}
	if (cmd[2])
	{
		data->end = 0;
		g_exit_status = 1;
		ft_dprintf(2, "exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	data->end = 1;
	g_exit_status = nb;
	return (nb);
}
