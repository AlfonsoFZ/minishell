/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:37:53 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 13:45:38 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	if ((c == ' ') || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	skipspace(char *cmd, int *i)
{
	int	j;

	j = *i;
	while (cmd[j] && ft_isspace(cmd[j]) && cmd[j + 1] != '\0')
		j++;
	*i = j;
}

int	ft_check_nquotes(t_data *dt)
{
	if (dt->dq_active == 1)
	{
		dt->error = ft_err_msg("", "", ERROR_DQUOTE, 2);
		return (2);
	}
	else if (dt->sq_active == 1)
	{
		dt->error = ft_err_msg("", "", ERROR_SQUOTE, 2);
		return (2);
	}
	return (0);
}

int	ft_check_quote(t_data *dt, char c)
{
	if (c == '\"' && dt->sq_active == 0)
		dt->dq_active ^= 1;
	else if (c == '\'' && dt->dq_active == 0)
		dt->sq_active ^= 1;
	return (0);
}

void	check_quotes(int *squoted, int *dquoted, char c)
{
	if (c == '\'')
	{
		if (*dquoted == 0)
			*squoted = !*squoted;
	}
	else if (c == '\"')
	{
		if (*squoted == 0)
			*dquoted = !*dquoted;
	}
}
