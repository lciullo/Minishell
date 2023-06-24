#include "minishell.h"

static char		*actualise_pwd(char *actual_path, t_env **lst);
static size_t	get_nb_arguments(char **cmd);
static	int		get_old_pwd(char *old_pwd, t_env **lst);

int	implement_cd(char **cmd, t_env **lst)
{
	int		nb_arg;
	char	*actual_path;
	char	*old_pwd;

	nb_arg = 0;
	old_pwd = NULL;
	actual_path = NULL;
	nb_arg = get_nb_arguments(cmd);
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			g_exit_status = 2;
			ft_dprintf(2, "Invalid option, subject : cd with no options\n");
			return (FAILURE);
		}
	}
	if (nb_arg > 2)
	{
		g_exit_status = 1;
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (FAILURE);
	}
	if (nb_arg == 1)
	{
		g_exit_status = 1;
		ft_dprintf(2, "subject: cd with only a relative or absolute path\n");
		return (FAILURE);
	}
	if (nb_arg == 2)
	{
		if (chdir(cmd[1]) == -1)
		{
			ft_dprintf(2, "chdir: error retrieving current directory: \
			getcwd: cannot access parent directories: No such file or directory\n");
			g_exit_status = 1;
			return (FAILURE);
		}
		actual_path = getcwd(NULL, 0);
		if (actual_path == NULL)
		{
			ft_dprintf(2, "minishell: cd: path not foumd\n");
			g_exit_status = 1;
			return (FAILURE);
		}
		old_pwd = actualise_pwd(actual_path, lst);
		get_old_pwd(old_pwd, lst);
		free(actual_path);
		g_exit_status = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

static size_t	get_nb_arguments(char **cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (FAILURE);
	while (cmd[i] != NULL)
		i++;
	return (i);
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
