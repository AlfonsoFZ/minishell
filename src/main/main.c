/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:57:16 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/22 12:23:48 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_s_status;

int	ft_cmd_interpreter(int i, t_data *dt, t_cmnd *cmnd)
{
	if (i == 1)
		return (ft_env(dt, cmnd));
	else if (i == 6)
		return (ft_cd(dt, cmnd));
	else if (i == 2)
		return (ft_exit(dt, cmnd));
	else if (i == 5)
		return (ft_unset(dt, cmnd));
	else if (i == 4)
		return (ft_export(dt, cmnd));
	else if (i == 7)
		return (ft_pwd(dt, cmnd));
	else if (i == 8)
		return (ft_echo(cmnd));
	return (0);
}

int	check_builtin(char *str)
{
	if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (2);
	else if (ft_strcmp(str, "clear") == 0)
		return (3);
	else if (ft_strcmp(str, "export") == 0)
		return (4);
	else if (ft_strcmp(str, "unset") == 0)
		return (5);
	else if (ft_strcmp(str, "cd") == 0)
		return (6);
	else if (ft_strcmp(str, "pwd") == 0)
		return (7);
	else if (ft_strcmp(str, "echo") == 0)
		return (8);
	return (0);
}

int	is_builtin(t_data *dt, t_cmnd *cmnd, int i)
{
	int	builtin;

	builtin = 0;
	if (!cmnd->args || !cmnd->args[0] || cmnd->io_error)
		return (0);
	builtin = check_builtin(dt->cmnd[i]->args[0]);
	if (builtin)
	{
		if (fill_redirect(dt, dt->cmnd[i], i))
			exit (1);
		dt->error = ft_cmd_interpreter(builtin, dt, dt->cmnd[i]);
		if (dt->n_pipes == 0)
		{
			ft_close_redir(cmnd);
			if (dt->user_input)
				ft_free_dt(dt);
		}
		return (1);
	}
	return (dt->error);
}

int	run_minishell(t_data *dt, int i)
{
	while (1 && ++i)
	{
		signal(SIGINT, ft_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		if (init_dt(dt, i))
			return (1);
		if (i > 2)
			dt->user_input = read_prompt(dt);
		if (!dt->user_input && i > 2)
			ft_ctrl_d(dt, dt->user_input);
		if (dt->user_input && *dt->user_input)
		{
			if (check_dir_permiss(get_value(&(dt->env_lst), "PWD"))
				|| parser(dt)
				|| (dt->n_pipes == 0 && is_builtin(dt, dt->cmnd[0], 0)))
				continue ;
			else
			{
				red_execute(dt);
				if (dt->user_input)
					ft_free_dt(dt);
			}
		}
	}
	return (0);
}

int	main(int ac, char **argv, char **env)
{
	t_data	dt;
	int		i;

	(void)ac;
	(void)argv;
	ft_print_minishell_title();
	ft_memset(&dt, 0, sizeof(t_data));
	first_init_dt(&dt, env);
	i = 0;
	rl_catch_signals = 0;
	if (run_minishell(&dt, i))
		return (1);
	final_free(&dt);
	return (dt.error);
}
