/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:09:16 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 18:49:21 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_signals_proccess(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_s_status = 1;
		errno = 130;
	}
}

void	ft_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		errno = 130;
		g_s_status = 1;
	}
}

void	ft_ctrl_c_pipe(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		errno = 1;
		g_s_status = 1;
	}
}

void	ft_signal_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	errno = 1;
	g_s_status = 3;
}

int	ft_ctrl_d(t_data *dt, char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		ft_free_dt(dt);
		exit (0);
	}
	return (1);
}
