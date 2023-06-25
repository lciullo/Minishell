#include "minishell.h"

void	error_message_cd(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4)
		g_exit_status = 1;
	if (type == 0)
	{
		g_exit_status = 2;
		ft_dprintf(2, "Invalid option, subject : cd with no options\n");
	}
	else if (type == 1)
		ft_dprintf(2, "minishell: cd: too many arguments\n");
	else if (type == 2)
		ft_dprintf(2, "subject: cd with only a relative or absolute path\n");
	else if (type == 3)
		ft_dprintf(2, "subject: cd with only a relative or absolute path\n");
	else if (type == 4)
	{
		ft_dprintf(2, "chdir: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or directory\n");
	}
}

size_t	get_nb_arguments(char **cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (FAILURE);
	while (cmd[i] != NULL)
		i++;
	return (i);
}

char	*find_old_path(char *actual_path, t_env **lst)
{
	t_env	*copy;
	char	*old_path;

	old_path = NULL;
	copy = *lst;
	while (copy != NULL)
	{
		if (ft_strcmp(copy->name, "PWD") == 0)
		{
			if (copy->value[0] != '\0')
			{
				old_path = ft_strdup(copy->value);
				if (!old_path)
					return (NULL);
				return (old_path);
			}
		}
		copy = copy->next;
	}
	old_path = ft_strdup(actual_path);
	if (!old_path)
	{
		ft_dprintf(2, "faillure in second strdup\n");
		return (NULL);
	}
	return (old_path);
}

void	clear_actualise_pwd(char *actual_path, char *old_path)
{
	if (actual_path)
		free(actual_path);
	if (old_path)
		free(old_path);
}
