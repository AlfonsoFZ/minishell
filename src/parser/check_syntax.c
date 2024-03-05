/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:34:25 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 12:28:02 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_next_del(char *s, int *i, t_data *dt, int len)
{
	int	j;

	j = *i + 1;
	while (s[j] == ' ' && j < len)
		j++;
	if (s[j] == '<' && (s[j + 1] == '<' && (s[j + 2] == '<')))
		return (set_error(dt, ERROR_TRIPINF));
	else if (s[j] == '<' && (s[j + 1] == '<'))
		return (set_error(dt, ERROR_DINCAR));
	else if (s[j] == '<' && (s[j + 1] == '>'))
		return (set_error(dt, ERROR_INOUTCAR));
	else if (s[j] == '<')
		return (set_error(dt, ERROR_INFCAR));
	else if (s[j] == '>' && s[j + 1] == '>')
		return (set_error(dt, ERROR_DOUTCAR));
	else if (s[j] == '>')
		return (set_error(dt, ERROR_OUTCAR));
	while (s[j] == ' ' && j < len)
		j++;
	if (s[j] == '|')
		return (set_error(dt, ERROR_SPIPE));
	if (j == len || !s[j])
		return (set_error(dt, ERROR_ENDLINE));
	return (0);
}

static	int	check_in_syntax(char *s, int *i, t_data *dt, int len)
{
	int	j;

	j = *i + 1;
	if (s[j] == '<')
	{
		*i = j;
		if (s[j + 1] == ' ' || s[j + 1] == '|' || s[j + 1] == '\0')
			return (ft_check_next_del(s, i, dt, len));
		if (s[j + 1] == '<')
			return (set_error(dt, ERROR_TRIPINF));
	}
	else if (s[j] == '>')
		*i = j;
	return (ft_check_next_del(s, i, dt, len));
}

static int	check_out_syntax(char *s, int *i, t_data *dt, int len)
{
	int	j;

	j = *i + 1;
	if (s[j] == '>')
	{
		*i = j;
		if (s[j + 1] == ' ' || s[j + 1] == '|' || s[j + 1] == '\0')
			return (ft_check_next_del(s, i, dt, len));
	}
	return (ft_check_next_del(s, i, dt, len));
}

static int	check_psyntax(char **s, int *i, t_data *dt)
{
	int	j;

	j = 0;
	while ((*s)[j] == ' ')
		j++;
	if (*i == j)
		return (ft_err_msg("", "", ERROR_SPIPE, 258));
	(*i)++;
	while ((*s)[*i] == ' ')
		(*i)++;
	if ((*s)[*i] == '|')
		return (ft_err_msg("", "", ERROR_SPIPE, 258));
	if (*i == (int)ft_strlen(*s))
		if (ft_get_next_pipe(s, dt))
			return (dt->error);
	return (0);
}

int	check_syntax(t_data *dt, char **s, int i)
{
	int		len;

	len = ft_strlen(*s);
	while (++i < len && dt->error == 0)
	{
		ft_check_quote(dt, (*s)[i]);
		if ((*s)[i] == '<' && (dt->dq_active == 0 && dt->sq_active == 0))
			dt->error = check_in_syntax(*s, &i, dt, len);
		else if (((*s)[i] == '>' && (dt->dq_active == 0 && dt->sq_active == 0)))
			dt->error = check_out_syntax(*s, &i, dt, len);
		else if (((*s)[i] == '|' && dt->sq_active == 0 && dt->dq_active == 0))
			dt->error = check_psyntax(s, &i, dt);
	}
	dt->sq_active = 0;
	dt->dq_active = 0;
	return (dt->error);
}
