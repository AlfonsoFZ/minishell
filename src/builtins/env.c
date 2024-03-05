/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:12:18 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/11 11:50:09 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_env(t_data *dt, t_cmnd *cmnd);
int		ft_env_arg(char **spltd_cmd);
int		ft_chk_env_arg(char *arg);

int	ft_chk_env_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == '-')
		i++;
	if (arg[i] != '\0' && i > 0)
	{
		ft_putstr_fd("env: options not requested in subject\n", 2);
		return (errno = 125, errno);
	}
	else if (arg[i] == '\0')
		rl_on_new_line();
	else
	{
		ft_putstr_fd("env: «", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("»: No such file or directory\n", 2);
		return (errno = 127, errno);
	}
	return (0);
}

int	ft_env_arg(char **spltd_cmd)
{
	int	i;

	i = 1;
	while (spltd_cmd[i])
	{
		if (ft_chk_env_arg(spltd_cmd[i]))
			return (errno);
		i++;
	}
	return (0);
}

int	ft_env(t_data *dt, t_cmnd *cmnd)
{
	if (ft_mtrxlen(cmnd->args) > 1)
	{
		if (ft_env_arg(cmnd->args))
			return (dt->error = errno, dt->error);
	}
	else
		ft_print_env_list(dt->env_lst);
	return (0);
}
