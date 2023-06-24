#include "minishell.h"

static char		*actualise_pwd(char *actual_path, t_env **lst);
static	int		get_old_pwd(char *old_pwd, t_env **lst);
static int		check_nb_arg(int nb_arg, char **cmd, t_env **lst);

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
	char	*old_pwd;

	old_pwd = NULL;
	actual_path = NULL;
	if (nb_arg > 2)
		return (error_message_cd(1), FAILURE);
	if (nb_arg == 1)
		return (error_message_cd(2), FAILURE);
	if (nb_arg == 2)
	{
		if (chdir(cmd[1]) == -1)
			return (error_message_cd(3), FAILURE);
		actual_path = getcwd(NULL, 0);
		if (actual_path == NULL)
			return (error_message_cd(4), FAILURE);
		old_pwd = actualise_pwd(actual_path, lst);
		get_old_pwd(old_pwd, lst);
		free(actual_path);
		g_exit_status = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

static	char	*actualise_pwd(char *actual_path, t_env **lst)
{
	t_env	*copy;
	char	*old_pwd;

	old_pwd = NULL;
	copy = *lst;
	while (copy != NULL)
	{
		if (ft_strcmp(copy->name, "PWD") == 0)
		{
			if (copy->value[0] != '\0')
				old_pwd = ft_strdup(copy->value);
			else
				copy->value = ft_strdup(actual_path);
			return (old_pwd);
		}
		copy = copy->next;
	}
	return (NULL);
}

static	int	get_old_pwd(char *old_pwd, t_env **lst)
{
	t_env	*copy;

	copy = *lst;
	while (copy != NULL)
	{
		if (ft_strcmp(copy->name, "OLDPWD") == 0)
		{
			if (copy->value)
				free(copy->value);
			copy->value = old_pwd;
			copy->equal = 1;
			return (SUCCESS);
		}
		copy = copy->next;
	}
	return (FAILURE);
}
