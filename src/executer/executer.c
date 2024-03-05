/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:46:19 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 17:18:55 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_data *dt, t_cmnd *cmnd, int i);
int	check_builtin(char *str);
int	ft_cmd_interpreter(int i, t_data *dt, t_cmnd *cmnd);

void	ft_execute(t_data *dt, char**args, int i, char **env)
{
	char	*resok;

	resok = NULL;
	if (ft_strchr(dt->cmnd[i]->args[0], '/'))
		resok = ft_strdup(dt->cmnd[i]->args[0]);
	else
	{
		if (!ft_is_in_env_lst("PATH", dt->env_lst))
		{
			ft_err_msg(dt->cmnd[i]->args[0], ": ", strerror(2), 127);
			exit (127);
		}
		resok = getpath(args[0], env, -1, resok);
	}
	if (resok)
		execve(resok, args, env);
	if (resok && resok[0] != '\0')
		ft_freenull(resok);
	ft_check_free(dt, dt->cmnd[i]->args[0]);
}

int	weror(t_data *dt, int i)
{
	int	status;
	int	status_code;

	status_code = 0;
	status = 0;
	while (++i <= dt->n_pipes)
	{
		waitpid(dt->n_pid[i], &status, 0);
		if (WIFEXITED(status))
			status_code = WEXITSTATUS(status);
	}
	return (status_code);
}

void	child_process(t_data *dt, int i)
{
	if (i == 0 && dt->n_pipes > 0)
		close(dt->pipes[i][0]);
	if (is_builtin(dt, dt->cmnd[i], i) && dt->n_pipes > 0)
		exit (dt->error);
	else
	{
		if (fill_redirect(dt, dt->cmnd[i], i))
			exit (1);
		if (dt->cmnd[i]->args && dt->cmnd[i]->args[0])
			ft_execute(dt, dt->cmnd[i]->args, i, dt->env);
	}
	exit (0);
}

static int	pipe_exec(t_data *dt, int i)
{
	while (++i <= dt->n_pipes)
	{
		ft_create_pipe(dt, i);
		dt->n_pid[i] = fork();
		if (dt->n_pid[i] < 0)
			return (errno);
		if (dt->n_pid[i] == 0)
			child_process(dt, i);
		else
		{
			if (i < dt->n_pipes)
				close(dt->pipes[i][1]);
			if (i > 0)
				close(dt->pipes[i - 1][0]);
		}
	}
	dt->error = weror(dt, -1);
	return (0);
}

int	red_execute(t_data *dt)
{
	int	i;

	i = -1;
	signal(SIGINT, ft_signals_proccess);
	signal(SIGQUIT, SIG_IGN);
	if (dt->n_pipes > 0)
		dt->pipes = ft_create_pipes(dt->n_pipes);
	dt->n_pid = (pid_t *)malloc(sizeof(pid_t *) * (dt->n_pipes + 1));
	if (pipe_exec(dt, i))
		return (errno);
	if (dt->n_pipes == 0 && dt->cmnd[0]->args && dt->cmnd[0]->args[0])
	{
		if (dt->last_cmnd_arg)
			ft_freenull(dt->last_cmnd_arg);
		dt->last_cmnd_arg = ft_strdup(get_last_arg(dt));
	}
	if (dt->n_pipes)
		free_array(dt->pipes, dt->n_pipes);
	free(dt->n_pid);
	dt->last_exit = dt->error;
	if (g_s_status == 1 || g_s_status == 2)
		dt->error = (g_s_status + 129);
	return (dt->error);
}
