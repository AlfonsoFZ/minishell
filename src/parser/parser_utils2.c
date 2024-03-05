/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:37:53 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/22 10:29:56 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_error(t_data *dt, char *error)
{
	dt->error = (ft_err_msg("", "", error, 258), 258);
	return (dt->error);
}

void	set_io_error(t_cmnd *cmnd, char *str, int ernb)
{
	if (!cmnd->io_error)
	{
		cmnd->io_error_name = ft_strdup(str);
		cmnd->io_error = ernb;
	}
}

char	*ft_free_join(char *s1, char *s2, int strtofree)
{
	char		*dest;
	size_t		i;
	size_t		j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	dest = (char *)ft_calloc(((ft_strlen(s1) + ft_strlen(s2) + 1)), 1);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		dest[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i] = '\0';
	if (strtofree == 1)
		free(s1);
	else if (strtofree == 2)
		free(s2);
	else if (strtofree == 3)
	{
		ft_freenull(s1);
		ft_freenull(s2);
	}
	return (dest);
}

char	*ft_return_in_var(t_cmnd *cmnd, int *i, int sqdq[2], int ix)
{
	char	*res;

	res = ft_strdup("");
	res = ft_free_join(res, ft_get_var(cmnd, i, sqdq[1], ix), 3);
	if (res && ft_strchr(res, ' ') && !sqdq[1])
	{
		cmnd->ambiguous = 1;
	}
	return (res);
}
