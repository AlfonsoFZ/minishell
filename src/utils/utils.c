/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:52:58 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/22 11:24:17 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_err_msg_n(char *str1, char *str2, char *str3, int ernb)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putstr_fd(str3, STDERR_FILENO);
	return (ernb);
}

int	ft_err_msg(char *str1, char *str2, char *str3, int ernb)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putendl_fd(str3, STDERR_FILENO);
	return (ernb);
}

void	ft_closefds(int fd1[2], int filefd[2])
{
	close(fd1[0]);
	close(fd1[1]);
	close(filefd[0]);
	close(filefd[1]);
}
