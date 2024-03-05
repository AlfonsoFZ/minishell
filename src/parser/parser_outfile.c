/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:55:23 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 15:08:37 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_name(t_cmnd *cmnd, int *i, int ix)
{
	char	*res;
	int		sqdq[2];
	char	*s;

	sqdq[0] = 0;
	sqdq[1] = 0;
	s = cmnd->dt->cmds[ix];
	res = NULL;
	while (cmnd->dt->cmds[ix][++(*i)])
	{
		check_quotes(&sqdq[0], &sqdq[1], s[*i]);
		if (!sqdq[0] && !sqdq[1] && (ft_strchr(">< ", s[*i])))
		{
			if (s[*i] == '>' || s[*i] == '<')
				(*i)--;
			return (res);
		}
		else if (s[*i] == '$' && !sqdq[0] && s[(*i) + 1] != ' ')
			res = ft_free_join(res, ft_returnvar(cmnd, i, sqdq, ix), 3);
		else if ((s[*i] != ' ' && s[*i] != '\'' && s[*i] != '\"')
			|| (s[*i] == ' ' && (sqdq[1] || sqdq[0]))
			|| (s[*i] == '\'' && sqdq[1]) || (s[*i] == '\"' && sqdq[0]))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
	}
	return (res);
}

static int	open_outfile(t_cmnd *cmnd, int append)
{
	if (ft_strchr(cmnd->outfile, '/') && isdir(cmnd, cmnd->outfile))
		return (cmnd->dt->error);
	if (append == 1)
	{
		cmnd->fd_out = open(cmnd->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
		cmnd->out_append = 1;
	}
	else
		cmnd->fd_out = open(cmnd->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmnd->fd_out == -1)
	{
		if (access(cmnd->outfile, F_OK) == -1)
			set_io_error(cmnd, cmnd->outfile, ENOENT);
		else
			set_io_error(cmnd, cmnd->outfile, EACCES);
		return (1);
	}
	return (0);
}

static int	ft_check_amb(t_cmnd *cmnd, int ix)
{
	(void) ix;
	if ((!cmnd->outfile[0] && ft_strchr (cmnd->grossname, '$'))
		|| (cmnd->ambiguous == 1))
	{
		if (ft_strchr(cmnd->grossname, '"')
			|| ft_strchr(cmnd->grossname, '\''))
		{
			set_io_error(cmnd, cmnd->outfile, 2);
			cmnd->ambiguous = 0;
			return (0);
		}
		cmnd->fd_out = -1;
		set_io_error(cmnd, cmnd->grossname, 3);
		cmnd->ambiguous = 0;
		return (1);
	}
	cmnd->ambiguous = 0;
	return (0);
}

int	create_outfile(t_cmnd *cmnd, int *i, int append, int ix)
{
	char	*cmd;

	if (cmnd->dt->cmds[ix] == NULL)
		return (0);
	cmd = cmnd->dt->cmds[ix];
	(*i)++;
	skipspace(cmd, i);
	(*i)--;
	cmnd->grossname = ft_getgrosname(cmnd, *i, ix);
	cmnd->outfile = ft_get_name(cmnd, i, ix);
	ft_check_amb(cmnd, ix);
	ft_freenull(cmnd->grossname);
	if (cmnd->fd_out != -1 && cmnd->io_error == 0)
	{
		if (cmnd->fd_out != 1)
			close(cmnd->fd_out);
		cmnd->dt->error = open_outfile(cmnd, append);
		if (cmnd->fd_out > 1)
			close(cmnd->fd_out);
		return (0);
	}
	return (0);
}

void	checkoutfile(t_cmnd *cmnd, char *cmd, int *i, int ix)
{
	int	j;

	j = *i;
	if (cmnd->io_error)
		ft_freenull(cmnd->outfile);
	else if (cmnd->fd_out > 1)
	{
		close (cmnd->fd_out);
		cmnd->fd_out = 1;
		cmnd->out_append = 0;
		ft_freenull(cmnd->outfile);
	}
	if (cmd[j + 1] && cmd[j + 1] == '>')
	{
		j++;
		*i = j;
		create_outfile(cmnd, i, 1, ix);
		return ;
	}
	skipspace(cmd, i);
	*i = j;
	create_outfile(cmnd, i, 0, ix);
}
