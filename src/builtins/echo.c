/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:46:52 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 19:57:39 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_cmnd *cmnd)
{
	int	i;
	int	endflag;

	i = 0;
	endflag = 0;
	if (!cmnd->args[1])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	endflag = ft_strncmp(cmnd->args[1], "-n", 3);
	if (!endflag)
		i++;
	while (cmnd->args[++i])
	{
		ft_putstr_fd(cmnd->args[i], STDOUT_FILENO);
		if (cmnd->args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (endflag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
