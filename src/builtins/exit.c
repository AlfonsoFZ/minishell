/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:59:00 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 14:15:35 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

long long	ft_long_atoi(const char *str)
{
	int			i;
	long long	num;
	long long	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		num = (str[i] - '0' + num * 10);
		i++;
	}
	return (num * sign);
}

void	ft_check_sign(char *str, int *i, int *flag)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*flag = 1;
		(*i)++;
	}
}

void	ft_check_zero(char *str, int *i)
{
	while (str[*i] == '0')
		i++;
}

int	ft_islonglong(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	ft_check_sign(str, &i, &flag);
	ft_check_zero(str, &i);
	if (ft_strlen(str + i) > 19)
		return (1);
	else if (ft_strlen(str + i) == 19)
	{
		if (flag == 1 && ft_strncmp(str + i, "9223372036854775808", 19) > 0)
			return (1);
		if (flag == 0 && ft_strncmp(str + i, "9223372036854775807", 19) > 0)
			return (1);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_data *dt, t_cmnd *cmnd)
{
	if (cmnd->args[0] && ft_strcmp(cmnd->args[0], "exit") == 0 \
		&& dt->n_pid == 0)
		ft_putendl_fd("exit", 1);
	if ((cmnd->args[1] && ft_islonglong(cmnd->args[1])))
	{
		ft_err_msg("exit: ", cmnd->args[1], ": numeric argument required", 2);
		exit (255);
	}
	else if (cmnd->args[1] && cmnd->args[2] && cmnd->args[3])
	{
		ft_err_msg("exit: ", "", "too many arguments", 1);
		return (dt->error = 1, 1);
	}
	else if (cmnd->args[1] && cmnd->args[2])
	{
		ft_err_msg("exit: ", "", "too many arguments", 1);
		return (dt->error = 1, 1);
	}
	else if (cmnd->args[1])
		exit (ft_long_atoi(cmnd->args[1]));
	else
		exit (dt->error);
	return (0);
}
