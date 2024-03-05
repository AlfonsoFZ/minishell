/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:30:10 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 13:32:00 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_io(t_data *dt, t_cmnd *cmnd)
{
	(void)dt;
	if (cmnd->io_error)
	{
		if (cmnd->io_error == 3)
			ft_err_msg(cmnd->io_error_name, ": ", ERROR_AMB, 1);
		else
			ft_err_msg(cmnd->io_error_name, ": ", strerror(cmnd->io_error), 2);
		return (2);
	}
	return (0);
}

int	reset_stdin_stdout(t_cmnd *cmnd)
{
	if (cmnd->fd_in > 0)
	{
		dup2(cmnd->orig_fd[0], STDIN_FILENO);
		close(cmnd->orig_fd[0]);
	}
	if (cmnd->fd_out > 1)
	{
		dup2(cmnd->orig_fd[1], STDOUT_FILENO);
		close(cmnd->orig_fd[1]);
	}
	return (0);
}
