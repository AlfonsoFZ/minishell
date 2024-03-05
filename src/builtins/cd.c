/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:09:26 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 16:00:31 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_special(t_cmnd *cmnd, char **npath)
{
	*npath = get_var_value(cmnd, "HOME");
	if (!npath || (*npath == NULL && !cmnd->args[1]))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (*npath);
}

char	*get_npath(t_cmnd *cmnd, char **npath)
{
	if (!cmnd->args[1])
		return (get_special(cmnd, npath));
	else if (ft_strcmp(cmnd->args[1], "~") == 0)
	{
		if (cmnd->dt->home)
			*npath = cmnd->dt->home;
		else
		{
			ft_putstr_fd("HOME was not set when th mini was launched\n", 2);
			*npath = NULL;
		}
	}
	else if (ft_strcmp(cmnd->args[1], "-") == 0)
	{
		if (!get_var_value(cmnd, "OLDPWD"))
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		else
		{
			ft_putendl_fd(get_var_value(cmnd, "OLDPWD"), 1);
			*npath = get_var_value(cmnd, "OLDPWD");
		}
	}
	else
		*npath = cmnd->args[1];
	return (*npath);
}

int	change_dir(char *npath, t_data *dt)
{
	char	cwd[1024];
	char	*opwd;

	opwd = get_pwd(dt);
	if (chdir(npath) == -1)
	{
		ft_err_msg_n("cd: ", npath, ": ", 1);
		perror("");
		return (-1);
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			ft_update_var("PWD", cwd, &(dt->env_lst));
			ft_update_var("OLDPWD", opwd, &(dt->env_lst));
		}
		else
		{
			ft_update_var("PWD", ft_strdup(change_pwd(dt, npath)), \
				&(dt->env_lst));
			ft_update_var("OLDPWD", dt->pwd, &(dt->env_lst));
		}
	}
	return (0);
}

int	ft_cd(t_data *dt, t_cmnd *cmnd)
{
	char	*npath;

	npath = get_npath(cmnd, &npath);
	if (!npath)
		return (dt->error = 1, errno = 1, errno);
	if (dt->n_pipes > 0)
		return (check_dir(npath), 0);
	if (check_dir_permiss(npath))
		return (dt->error = 0, errno = 0, errno);
	if (change_dir(npath, dt) == -1)
		return (dt->error = 1, errno = 1, errno);
	return (0);
}
