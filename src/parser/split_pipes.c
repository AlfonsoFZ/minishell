/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:36:00 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 13:51:23 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	ft_strlenc(t_data *dt, const char *s)
{
	size_t	i;
	int		tmpsq;
	int		tmpdq;

	i = 0;
	tmpsq = dt->sq_active;
	tmpdq = dt->dq_active;
	dt->dq_active = 0;
	dt->sq_active = 0;
	while (s[i])
	{
		ft_check_quote(dt, s[i]);
		if ((s[i] == '|' && dt->dq_active == 0)
			&& (s[i] == '|' && dt->sq_active == 0))
			break ;
		if (s[i] == '\0')
			break ;
		i++;
	}
	dt->dq_active = tmpdq;
	dt->sq_active = tmpsq;
	return (i);
}

static int	ft_countpipes(t_data *dt)
{
	int	i;

	i = -1;
	while (dt->user_input[++i])
	{
		if ((dt->user_input[i] == '|' && dt->sq_active == 0)
			&& (dt->user_input[i] == '|' && dt->dq_active == 0))
			dt->n_pipes++;
		else
			ft_check_quote(dt, dt->user_input[i]);
	}
	if (ft_check_nquotes(dt))
		return (2);
	return (0);
}

static char	**ft_createcmd(t_data *dt, char **res)
{
	size_t	t;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	t = 0;
	while (dt->user_input[i] && j < (size_t)dt->n_pipes + 1)
	{
		ft_check_quote(dt, dt->user_input[i]);
		if ((dt->user_input[i] != '|') || ((dt->user_input[i] == '|')
				&& ((dt->sq_active == 1) && dt->dq_active == 1)))
		{
			t = ft_strlenc (dt, &dt->user_input[i]);
			res[j++] = (ft_substr(&dt->user_input[i], 0, t));
			i = i + t;
			if (dt->user_input[i] == '|' && dt->user_input[i + 1] == '\0')
				res[j++] = ft_strdup("");
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split_pipes(t_data *dt)
{
	char	**res;
	int		i;

	i = 0;
	if (ft_countpipes(dt))
		return (NULL);
	res = ft_calloc(dt->n_pipes + 2, sizeof(char *));
	if (res == NULL)
		return (0);
	res = ft_createcmd(dt, res);
	while (i < dt->n_pipes + 1)
	{
		if (res[i] == NULL)
			ft_split_free(res);
		i++;
	}
	return (res);
}
