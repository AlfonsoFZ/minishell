/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inout_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:06:42 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 20:03:07 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getgrosname(t_cmnd *cmnd, int i, int ix)
{
	char	*res;
	int		sqdq[2];

	sqdq[0] = 0;
	sqdq[1] = 0;
	res = ft_strdup("");
	while (cmnd->dt->cmds[ix][++i])
	{
		check_quotes(&sqdq[0], &sqdq[1], cmnd->dt->cmds[ix][i]);
		if (((cmnd->dt->cmds[ix][i] == '>' || cmnd->dt->cmds[ix][i] == '<'
			|| cmnd->dt->cmds[ix][i] == ' ' ) && !sqdq[1] && !sqdq[0]))
			return (res);
		else
			res = ft_free_join(res, ft_substr(cmnd->dt->cmds[ix], i, 1), 3);
	}
	return (res);
}

int	is_last(t_cmnd *cmnd, int i, int ix)
{
	char	*s;

	s = cmnd->dt->cmds[ix];
	while (s[++i])
	{
		if (s[i] != ' ')
			return (1);
	}
	return (0);
}

char	*ft_returnvar(t_cmnd *cmnd, int *i, int sqdq[2], int ix)
{
	char	*res;
	char	*trim;

	trim = NULL;
	res = ft_strdup("");
	res = ft_free_join(res, ft_get_var(cmnd, i, sqdq[1], ix), 3);
	if (!sqdq[1] && ft_strchr(res, ' '))
	{
		if (!is_last(cmnd, *i, ix))
		{
			trim = ft_strtrim(res, " ");
			free(res);
			return (trim);
		}
	}
	if (res && ft_strchr(res, ' ') && !sqdq[1])
	{
		cmnd->ambiguous = 1;
	}
	return (res);
}

int	check_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (-1);
	if (S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}

int	isdir(t_cmnd *cmnd, char *outfile)
{
	char	*path;

	path = ft_substr(outfile, 0, ft_strlen(outfile) \
		- ft_strlen(ft_strrchr(outfile, '/')));
	if (check_directory(path) == -1)
	{
		set_io_error(cmnd, outfile, ENOENT);
		cmnd->fd_out = -1;
		return (1);
	}
	return (0);
}
