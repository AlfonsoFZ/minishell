/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hd_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:43:22 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 13:29:50 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_del(char *s, int *i, int squoted, int dquoted)
{
	char	*res;

	res = ft_strdup("");
	while (ft_isspace(s[(*i) + 1]))
		(*i)++;
	while (s[++(*i)])
	{
		check_quotes(&squoted, &dquoted, s[*i]);
		if ((s[*i] == '<' || s[*i] == '>') && !dquoted && !squoted)
		{
			(*i)--;
			return (res);
		}
		else if ((s[*i] == ' ') && !dquoted && !squoted)
			break ;
		else if ((s[*i] != ' ' && s[*i] != '\'' && s[*i] != '\"')
			|| (s[*i] == ' ' && (dquoted || squoted)))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
		else if ((s[*i] == '\'' && dquoted))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
		else if ((s[*i] == '\"' && squoted))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
	}
	return (res);
}

char	*set_delimiter(char *cmd, int *i, char *del, int *deltype)
{
	del = NULL;
	if (cmd[*i + 1] == '-')
	{
		ft_err_msg("", "", ERROR_HER_HIP, 0);
		(*i)++;
	}
	while (ft_isspace(cmd[(*i) + 1]))
		(*i)++;
	if (cmd[*i + 1] == '\'' || cmd[*i + 1] == '\"')
		*deltype = 1;
	del = ft_get_del(cmd, i, 0, 0);
	return (del);
}
