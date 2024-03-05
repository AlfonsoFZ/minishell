/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:45:33 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 13:39:28 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_freenull(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	ft_free_cmnds(t_data *dt, int i)
{
	if (dt->cmnd[i]->infile)
	{
		if (dt->cmnd[i]->in_heredoc == 1)
		{
			if (dt->cmnd[i]->fd_in != -1)
				close(dt->cmnd[i]->fd_in);
			if (unlink(dt->cmnd[i]->infile) == -1)
				perror("heredoc file cannot be deleted");
		}
		ft_freenull (dt->cmnd[i]->infile);
	}
	if (dt->cmnd[i]->outfile)
		ft_freenull (dt->cmnd[i]->outfile);
	if (dt->cmnd[i]->io_error)
		ft_freenull (dt->cmnd[i]->io_error_name);
	if (dt->cmnd[i]->argsstr)
		ft_freenull (dt->cmnd[i]->argsstr);
	if (dt->cmnd[i]->args)
	{
		if (dt->cmnd[i]->args[0])
			ft_free_array(dt->cmnd[i]->args);
		else
			ft_freenull(dt->cmnd[i]->args);
	}
}

void	ft_free_dt(t_data *dt)
{
	int	i;

	if (dt->user_input)
		ft_freenull(dt->user_input);
	if (dt->cmds && dt->cmds[0])
		ft_free_array(dt->cmds);
	i = -1;
	while (++i <= dt->n_pipes && dt->cmnd && dt->cmnd[i])
	{
		ft_free_cmnds(dt, i);
		ft_freenull(dt->cmnd[i]);
	}
	ft_freenull (dt->cmnd);
}

void	final_free(t_data *dt)
{
	if (dt->last_cmnd_arg)
		ft_freenull(dt->last_cmnd_arg);
	ft_free_env_lst(&dt->env_lst);
	ft_free_matrix(dt->env);
}
