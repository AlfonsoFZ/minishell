/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:53:44 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 13:57:26 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_to_next_quote(char *cmd, int *j, int *k)
{
	char	quote;

	quote = cmd[*j];
	(*j)++;
	(*k)++;
	while (cmd[*j] && cmd[*j] != quote)
	{
		(*j)++;
		(*k)++;
	}
	(*j)++;
	(*k)++;
}

char	*get_arg(char *cmd, int *i)
{
	int		j;
	int		k;
	char	*arg;
	char	*space;

	space = ft_strdup(" ");
	j = *i;
	k = 0;
	while (cmd[j] && !ft_isspace(cmd[j]) && cmd[j] != '>' && cmd[j] != '<')
	{
		if (cmd[j] == '\'' || cmd[j] == '\"')
			ft_to_next_quote(cmd, &j, &k);
		else
		{
			j++;
			k++;
		}
	}
	arg = ft_free_join(space, ft_substr(cmd, *i, k), 3);
	*i = j - 1;
	return (arg);
}

void	ft_fill(t_cmnd *cmnd, char *cmd, int ix)
{
	int	i;
	int	j;

	cmnd->argsstr = ft_strdup("");
	i = 0;
	j = ft_strlen(cmd);
	while (i < j)
	{
		if (cmd[i] && cmd[i] == '<')
			checkinfile(cmnd, cmd, &i, ix);
		else if (cmd[i] && cmd[i] == '>')
			checkoutfile(cmnd, cmd, &i, ix);
		else if (!ft_isspace(cmd[i]))
			cmnd->argsstr = ft_free_join(cmnd->argsstr, get_arg(cmd, &i), 3);
		i++;
	}
	if (cmnd->argsstr[0])
		cmnd->args = ft_split_pipex(cmnd);
}

static t_cmnd	*init_cmnd(t_data *dt, char *cmd, int i)
{
	t_cmnd	*cmnd;

	(void)cmd;
	cmnd = (t_cmnd *)ft_calloc(sizeof(t_cmnd), 1);
	if (!cmnd)
		return (NULL);
	cmnd->infile = NULL;
	cmnd->outfile = NULL;
	cmnd->grossname = NULL;
	cmnd->ambiguous = 0;
	cmnd->fd_in = 0;
	cmnd->fd_out = 1;
	cmnd->in_heredoc = 0;
	cmnd->out_append = 0;
	cmnd->io_error_name = NULL;
	cmnd->io_error = 0;
	cmnd->index = i;
	cmnd->argsstr = NULL;
	cmnd->args = NULL;
	cmnd->dt = dt;
	return (cmnd);
}

int	parse_cmd(t_data *dt, char **cmds)
{
	int	i;

	i = -1;
	dt->cmnd = (t_cmnd **)ft_calloc(sizeof(t_cmnd *), dt->n_pipes + 1);
	if (!dt->cmnd)
		return (1);
	while (++i < dt->n_pipes + 1)
	{
		dt->cmnd[i] = init_cmnd(dt, cmds[i], i);
		ft_fill(dt->cmnd[i], cmds[i], i);
	}
	return (0);
}
