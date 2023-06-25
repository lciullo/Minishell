#include "minishell.h"

static	int		get_old_path_in_list(char *old_path, t_env **lst);
static int		check_nb_arg(int nb_arg, char **cmd, t_env **lst);
static int		get_actual_path_in_list(char *actual_path, t_env **lst);
static int		actualise_pwd(char *actual_path, \
					char *old_path, t_env **lst);

int	implement_cd(char **cmd, t_env **lst)
{
	int		nb_arg;

	nb_arg = 0;
	nb_arg = get_nb_arguments(cmd);
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
			return (error_message_cd(0), FAILURE);
	}
	if (check_nb_arg(nb_arg, cmd, lst) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_nb_arg(int nb_arg, char **cmd, t_env **lst)
{
	char	*actual_path;
	char	*old_path;

	old_path = NULL;
	actual_path = NULL;
	if (nb_arg > 2)
		return (error_message_cd(1), FAILURE);
	if (nb_arg == 1)
		return (error_message_cd(2), FAILURE);
	if (nb_arg == 2)
	{
		if (chdir(cmd[1]) == -1)
			return (error_message_cd(3), FAILURE);
		if (actualise_pwd(actual_path, old_path, lst) == FAILURE)
			return (FAILURE);
		g_exit_status = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

static	int	actualise_pwd(char *actual_path, char *old_path, t_env **lst)
{
	actual_path = getcwd(NULL, 0);
	if (actual_path == NULL)
		return (error_message_cd(4), FAILURE);
	old_path = find_old_path(actual_path, lst);
	if (old_path == NULL)
	{
		if (actual_path)
			free(actual_path);
		return (FAILURE);
	}
	if (get_old_path_in_list(old_path, lst) == FAILURE)
	{
		clear_actualise_pwd(actual_path, old_path);
		return (FAILURE);
	}
	if (get_actual_path_in_list(actual_path, lst) == FAILURE)
	{
		if (actual_path)
			free(actual_path);
		return (FAILURE);
	}
	return (SUCCESS);
}

static	int	get_old_path_in_list(char *old_path, t_env **lst)
{
	t_env	*copy;

	copy = *lst;
	while (copy != NULL)
	{
		if (ft_strcmp(copy->name, "OLDPWD") == 0)
		{
			if (copy->value)
				free(copy->value);
			copy->value = old_path;
			copy->equal = 1;
			return (SUCCESS);
		}
		copy = copy->next;
	}
	return (FAILURE);
}

static	int	get_actual_path_in_list(char *actual_path, t_env **lst)
{
	t_env	*copy;

	copy = *lst;
	while (copy != NULL)
	{
		if (ft_strcmp(copy->name, "PWD") == 0)
		{
			if (copy->value)
				free(copy->value);
			copy->value = actual_path;
			copy->equal = 1;
			return (SUCCESS);
		}
		copy = copy->next;
	}
	return (FAILURE);
}
