/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:51:30 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 12:51:26 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_here_span(t_cmnd *cmnd, char *next, char **res)
{
	int		j;
	char	*varspan;

	j = 0;
	varspan = ft_strdup("");
	while (next[j])
	{
		if (next[j] == '$' && !ft_strchr("\'\"<>", next[j + 1]))
			varspan = ft_free_join(varspan, \
				ft_get_var_hd(cmnd, next, &j, 1), 3);
		else
			varspan = ft_free_join(varspan, ft_substr(next, j, 1), 3);
		j++;
	}
	*res = ft_free_join(*res, varspan, 3);
	*res = ft_free_join(*res, "\n", 1);
	varspan = NULL;
}

static int	*freenullthree(char *stra, char *strb, char *strc)
{
	if (stra)
	{
		free(stra);
		stra = NULL;
	}
	if (strb)
	{
		free(strb);
		strb = NULL;
	}
	if (strc)
	{
		free(strc);
		strc = NULL;
	}
	return (NULL);
}

void	get_valid_path(t_cmnd *cmnd, char **str)
{
	char	*s;

	s = NULL;
	s = get_var_value(cmnd, "PWD");
	if (s && *s && access(s, F_OK) == 0 && access(s, W_OK) == 0)
		*str = ".heredoc";
	else
	{
		s = "/tmp";
		*str = "/tmp/.heredoc";
		if (access(s, F_OK) == 0 && access(s, W_OK) == 0)
			return ;
	}
}

int	*create_heredoc(t_cmnd *cmnd, char *del, char *res, char *next)
{
	int		i;
	char	*name;
	int		fd;

	i = 0;
	name = NULL;
	fd = 1;
	get_valid_path(cmnd, &(cmnd->hdpath));
	while (fd < 2)
	{
		name = ft_free_join(ft_itoa(cmnd->index), ft_itoa(i), 3);
		name = ft_free_join(cmnd->hdpath, name, 2);
		fd = open(name, O_RDWR | O_CREAT | O_EXCL, 0666);
		if (fd <= 1)
			free(name);
		i++;
	}
	write(fd, res, ft_strlen(res));
	cmnd->infile = name;
	cmnd->in_heredoc = 1;
	close(fd);
	if (cmnd->fd_in != -1)
		cmnd->fd_in = fd;
	return (freenullthree(del, res, next));
}

int	*ft_get_heredoc(t_cmnd *cmnd, char *cmd, int *i)
{
	cmnd->del = NULL;
	cmnd->res = ft_strdup("");
	cmnd->next = NULL;
	cmnd->deltype = 0;
	cmnd->del = set_delimiter(cmd, i, cmnd->del, &cmnd->deltype);
	signal(SIGINT, ft_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (g_s_status == 3)
			return (freenullthree(cmnd->del, cmnd->res, cmnd->next));
		cmnd->next = readline("\001\033[1;32m\002>>\001\033[1;0m\002 ");
		if ((!cmnd->next) || ((cmnd->next && !ft_strncmp(cmnd->next, \
				cmnd->del, (ft_strlen(cmnd->del) + 1)))))
			return (create_heredoc(cmnd, cmnd->del, cmnd->res, cmnd->next));
		else if (cmnd->next && cmnd->deltype == 0)
			ft_here_span(cmnd, cmnd->next, &cmnd->res);
		else
		{
			cmnd->res = ft_free_join(cmnd->res, cmnd->next, 3);
			cmnd->res = ft_free_join(cmnd->res, "\n", 1);
		}
	}
	return (freenullthree(cmnd->del, cmnd->res, cmnd->next));
}
