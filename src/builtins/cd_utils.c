/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:44 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 15:46:03 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_dir_permiss(char *npath)
{
	if (access(npath, F_OK) == 0 && (access(npath, X_OK) != 0
			|| access(npath, R_OK) != 0 || access(npath, W_OK) != 0))
	{
		ft_err_msg_n("cd: ", npath, ": ", 0);
		return (ft_putendl_fd(FRIENDLY_MSG, 2), 1);
	}
	return (0);
}

char	*get_pwd(t_data *dt)
{
	char	*pwd;

	pwd = NULL;
	pwd = get_value(&(dt->env_lst), "PWD");
	if (!pwd || !*pwd)
		pwd = dt->pwd;
	return (pwd);
}

char	*change_pwd(t_data *dt, char *npath)
{
	char	*pwd;

	pwd = NULL;
	pwd = get_value(&(dt->env_lst), "PWD");
	if (!pwd || !*pwd)
		pwd = dt->pwd;
	else
		pwd = ft_strdup(npath);
	return (pwd);
}

void	check_dir(const char *dir_path)
{
	DIR	*dir;

	dir = opendir(dir_path);
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)dir_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit (2);
	}
	if (closedir(dir) == -1)
		perror("closedir");
}

void	ft_update_var(char *var_name, char *new_value, t_env **env)
{
	t_env	*current;

	current = *env;
	if (!new_value)
		return ;
	while (current && ft_strcmp(current->var_name, var_name) != 0)
		current = current->next;
	if (current && ft_strcmp(current->var_name, var_name) == 0)
	{
		if (current->var_value)
			free(current->var_value);
		current->var_value = ft_strdup(new_value);
	}
}
