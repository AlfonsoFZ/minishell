/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:54:06 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/22 10:04:38 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_get_ppid(t_data *dt)
{
	int		fd;
	char	buffer[9];
	ssize_t	bytes_read;

	fd = open(".afzppid", O_RDONLY);
	if (fd == -1)
		return (perror("a problem getting the ppid has occurred"), -1);
	bytes_read = read(fd, buffer, 9);
	if (bytes_read == -1)
	{
		perror("a problem getting the ppid has occurred");
		close(fd);
		unlink(".ppid");
		return (-1);
	}
	buffer[bytes_read] = '\0';
	dt->ppid = ft_atoi(buffer);
	close(fd);
	unlink(".afzppid");
	return (dt->ppid);
}

void	ft_special_var(t_data *dt)
{
	if (get_value(&(dt->env_lst), "HOME"))
	{
		free(dt->home);
		dt->home = ft_strdup(get_value(&(dt->env_lst), "HOME"));
	}
	if (get_value(&(dt->env_lst), "PWD"))
	{
		free(dt->pwd);
		dt->pwd = ft_strdup(get_value(&(dt->env_lst), "PWD"));
	}
}

/* MAC*/
bool	init_dt(t_data *dt, int i)
{
	ft_special_var(dt);
	g_s_status = 0;
	dt->user_input = NULL;
	if (i == 1)
		dt->user_input = ft_strdup("ps -a | grep ./minishell\
			| grep -v grep | tail -n 1 |awk '{print $1}' >.afzppid");
	dt->cmds = NULL;
	dt->n_pipes = 0;
	dt->pipes = NULL;
	dt->sq_counter = 0;
	dt->dq_counter = 0;
	dt->sq_active = 0;
	dt->dq_active = 0;
	dt->last_exit = dt->error;
	dt->error = 0;
	dt->path = NULL;
	dt->cmnd = NULL;
	dt->n_pid = NULL;
	if (i == 2)
		dt->ppid = ft_get_ppid(dt);
	if (i > 2)
	{
		ft_free_array(dt->env);
		ft_charge_env_mtrx_from_lst(&(dt->env_lst), &(dt->env));
	}
	return (false);
}

/* Linux
bool	init_dt(t_data *dt, int i)
{
	ft_special_var(dt);
	g_s_status = 0;
	dt->user_input = NULL;
	if (i == 1)
		dt->user_input = ft_strdup("ps -u |grep ./minishell | grep -v grep \
			| tail -n 1 |awk '{print $2}' >.afzppid");
	dt->cmds = NULL;
	dt->n_pipes = 0;
	dt->pipes = NULL;
	dt->sq_counter = 0;
	dt->dq_counter = 0;
	dt->sq_active = 0;
	dt->dq_active = 0;
	dt->last_exit = dt->error;
	dt->error = 0;
	dt->path = NULL;
	dt->cmnd = NULL;
	dt->n_pid = NULL;
	if (i == 2)
		dt->ppid = ft_get_ppid(dt);
	if (i > 2)
	{
		ft_free_array(dt->env);
		ft_charge_env_mtrx_from_lst(&(dt->env_lst), &(dt->env));
	}
	return (false);
}*/

bool	first_init_dt(t_data *dt, char **env)
{
	ft_charge_env_list(env, &(dt->env_lst));
	if (!ft_is_in_env_lst("PATH", dt->env_lst))
	{
		ft_err_msg("./minishell", ": ", strerror(2), 127);
		exit (127);
	}
	ft_special_var(dt);
	ft_index_env_lst(&(dt->env_lst));
	ft_charge_env_mtrx_from_lst(&(dt->env_lst), &(dt->env));
	dt->error = 0;
	dt->last_cmnd_arg = ft_strdup("./minishell");
	dt->last_exit = 0;
	dt->last_exit_str = NULL;
	dt->ppid = 0;
	return (true);
}
// dt->user_input = 
//	ft_strdup("ps -u |grep .//minishell | grep -v grep
//		| tail -n 1 |awk '{print $2}' >.afzppid"); //versión Linux
