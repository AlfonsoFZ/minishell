/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:01:25 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 13:31:13 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_close_redir(t_cmnd *cmnd)
{
	reset_stdin_stdout(cmnd);
	if (!cmnd->io_error)
	{
		if (cmnd->fd_in > 0)
			close(cmnd->fd_in);
		if (cmnd->fd_out > 1)
			close(cmnd->fd_out);
	}
	return (0);
}

int	ft_open_redir(t_data *dt, t_cmnd *cmnd)
{
	if (ft_check_io(dt, cmnd))
		return (1);
	if (cmnd->infile && cmnd->infile[0])
	{
		cmnd->fd_in = open(cmnd->infile, O_RDONLY);
		if (cmnd->fd_in < 0)
		{
			printf("Error opening file %s\n", cmnd->infile);
			return (1);
		}
	}
	if (cmnd->outfile && cmnd->outfile[0])
	{
		if (cmnd->out_append)
			cmnd->fd_out = open(cmnd->outfile, 01 | O_CREAT | O_APPEND, 0644);
		else
			cmnd->fd_out = open(cmnd->outfile, 01 | O_CREAT | O_TRUNC, 0644);
		if (cmnd->fd_out < 0)
		{
			printf("Error opening file %s\n", cmnd->outfile);
			return (1);
		}
	}
	return (0);
}

static int	ft_redir_in(t_data *dt, t_cmnd *cmnd, int i)
{
	if (cmnd->fd_in > 0)
	{
		cmnd->orig_fd[0] = dup(STDIN_FILENO);
		dup2(cmnd->fd_in, STDIN_FILENO);
		close(cmnd->fd_in);
	}
	else if (i > 0)
	{
		if (i > 0)
		{
			dup2(dt->pipes[i - 1][0], STDIN_FILENO);
			close(dt->pipes[i - 1][0]);
		}
	}
	return (0);
}

static int	ft_redir_out(t_data *dt, t_cmnd *cmnd, int i)
{
	if (cmnd->fd_out > 1)
	{
		cmnd->orig_fd[1] = dup(STDOUT_FILENO);
		dup2(cmnd->fd_out, STDOUT_FILENO);
		close(cmnd->fd_out);
	}
	else if (i != dt->n_pipes)
	{
		dup2(dt->pipes[i][1], STDOUT_FILENO);
		close(dt->pipes[i][1]);
	}
	return (0);
}

int	fill_redirect(t_data *dt, t_cmnd *cmnd, int i)
{
	if (g_s_status == 3)
	{
		cmnd->in_heredoc = 1;
		return (1);
	}
	if (ft_open_redir(dt, cmnd))
		return (1);
	ft_redir_in(dt, cmnd, i);
	ft_redir_out(dt, cmnd, i);
	return (0);
}
