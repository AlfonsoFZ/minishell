/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:53:58 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/22 11:18:38 by alfofern         ###   ########.fr       */
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
			res = ft_free_join(res, ft_return_in_var(cmnd, i, sqdq, ix), 3);
		else if ((s[*i] != ' ' && s[*i] != '\'' && s[*i] != '\"')
			|| (s[*i] == ' ' && (sqdq[1] || sqdq[0]))
			|| (s[*i] == '\'' && sqdq[1]) || (s[*i] == '\"' && sqdq[0]))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
	}
	return (res);
}

static int	ft_check_amb(t_cmnd *cmnd, int ix)
{
	(void) ix;
	if ((!cmnd->infile[0] && ft_strchr (cmnd->grossname, '$'))
		|| (cmnd->ambiguous == 1))
	{
		if (ft_strchr(cmnd->grossname, '"')
			|| ft_strchr(cmnd->grossname, '\''))
		{
			cmnd->ambiguous = 0;
			return (0);
		}
		cmnd->fd_in = -1;
		set_io_error(cmnd, cmnd->grossname, 3);
		cmnd->ambiguous = 0;
		return (1);
	}
	cmnd->ambiguous = 0;
	return (0);
}

int	create_infile(t_cmnd *cmnd, char *cmd, int *i, int ix)
{
	(*i)++;
	skipspace(cmd, i);
	(*i)--;
	if (cmnd->fd_in > 0)
		ft_freenull(cmnd->infile);
	cmnd->grossname = ft_getgrosname(cmnd, *i, ix);
	cmnd->infile = ft_get_name(cmnd, i, ix);
	ft_check_amb(cmnd, ix);
	ft_freenull(cmnd->grossname);
	if (cmnd->fd_in != -1)
	{
		if (cmnd->fd_in != 0)
			close(cmnd->fd_in);
		cmnd->fd_in = open(cmnd->infile, O_RDONLY);
		if (cmnd->fd_in == -1)
		{
			set_io_error(cmnd, cmnd->infile, errno);
			return (1);
		}
	}
	return (0);
}

static void	reset_infile(t_cmnd *cmnd)
{
	if (cmnd->fd_in > 0)
	{
		close(cmnd->fd_in);
		cmnd->fd_in = 0;
		cmnd->ambiguous = 0;
	}
	if (cmnd->infile)
	{
		if (cmnd->in_heredoc == 1)
			unlink(cmnd->infile);
		cmnd->in_heredoc = 0;
		ft_freenull(cmnd->infile);
	}
}

void	checkinfile(t_cmnd *cmnd, char *cmd, int *i, int ix)
{
	int	j;

	j = *i;
	reset_infile(cmnd);
	if (cmd[j + 1] && cmd[j + 1] == '<')
	{
		j++;
		*i = j;
		ft_get_heredoc(cmnd, cmd, i);
		return ;
	}
	else if (cmd[j + 1] == '>')
	{
		(*i)++;
		checkoutfile(cmnd, cmd, i, ix);
		cmnd->fd_out = 1;
		return ;
	}
	skipspace(cmd, i);
	*i = j;
	create_infile(cmnd, cmd, i, ix);
	if (cmnd->fd_in > 0)
		close(cmnd->fd_in);
}
