/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:24:02 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 12:51:37 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_get_next_pipe(char **s, t_data *dt)
{
	char	*pipe_input;
	int		i;

	i = -1;
	signal(SIGINT, ft_ctrl_c_pipe);
	signal(SIGQUIT, ft_ctrl_c_pipe);
	pipe_input = readline("\001\033[1;32m\002>\001\033[1;0m\002 ");
	if (pipe_input == NULL)
	{
		ft_err_msg("syntax error: ", "unexpected end of file", "", 2);
		return (dt->error = 2, 2);
	}
	if (g_s_status == 1)
		return (free(pipe_input), dt->error = 1, 1);
	*s = ft_free_join(*s, pipe_input, 3);
	if (!s)
		return (1);
	if (*s)
		i = check_syntax(dt, s, -1);
	if (i > 0)
		return (1);
	return (0);
}

int	**ft_create_pipes(int n_pipes)
{
	int	i;
	int	**pipes;

	i = -1;
	pipes = (int **)ft_calloc(sizeof(int *), (n_pipes));
	if (pipes == NULL)
	{
		ft_err_msg("", "", "memory allocation error\n", 1);
		return (NULL);
	}
	while (++i < n_pipes)
	{
		pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (pipes[i] == NULL)
		{
			ft_err_msg("", "", "memory allocation error\n", 1);
			return (NULL);
		}
	}
	return (pipes);
}

void	free_array(int **array, int n_pipes)
{
	int	i;

	i = -1;
	while (++i < n_pipes)
		free(array[i]);
	free(array);
}

int	ft_create_pipe(t_data *dt, int i)
{
	if ((dt->n_pipes > 0 && i != dt->n_pipes))
	{
		if (i < dt->n_pipes)
			if (pipe(dt->pipes[i]) == -1)
				return (1);
	}
	return (0);
}
