/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:46:01 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 15:27:28 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_string(t_cmnd *cmnd, int *i, int squoted, int dquoted)
{
	char	*res;
	char	*s;

	s = cmnd->argsstr;
	res = ft_strdup("");
	while (s[*i])
	{
		check_quotes(&squoted, &dquoted, s[*i]);
		if (s[*i] == '$' && !squoted && s[(*i) + 1] != ' ')
			res = ft_free_join(res, ft_get_var_hd(cmnd, s, i, dquoted), 3);
		else if ((s[*i] != ' ' && s[*i] != '\'' && s[*i] != '\"')
			|| (s[*i] == ' ' && (dquoted || squoted)))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
		else if ((s[*i] == '\'' && dquoted))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
		else if ((s[*i] == '\"' && squoted))
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
		else if (s[*i] == ' ' && !dquoted && !squoted)
		{
			(*i)++;
			return (res);
		}
		(*i)++;
	}
	return (res);
}

char	**ft_createstrings(t_cmnd *cmnd, char **res, int k)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (j < k)
	{
		res[j] = ft_get_string(cmnd, &i, 0, 0);
		j++;
	}
	res[j] = NULL;
	return (res);
}

static char	*clean_res(char *s, int squoted, int dquoted)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (s[i] == ' ' && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		check_quotes(&squoted, &dquoted, s[i]);
		if (s[i] == ' ' && s[i + 1] == ' ' && !squoted && !dquoted)
		{
			i++;
			continue ;
		}
		if (s[i] == ' ' && s[i + 1] == '\0')
		{
			i++;
			continue ;
		}
		res = ft_free_join(res, ft_substr(s, i, 1), 3);
		i++;
	}
	return (res);
}

static char	*ft_spanvar(char *s, t_cmnd *cmnd, int squoted, int dquoted)
{
	int		i;
	char	*res;

	i = -1;
	if (s == NULL)
		return (NULL);
	res = ft_strdup("");
	while (s[++i])
	{
		check_quotes(&squoted, &dquoted, s[i]);
		if (s[i] == '$' && !squoted && s[i + 1] != ' ' && !dquoted)
			res = ft_free_join(res, ft_get_var_hd(cmnd, s, &i, dquoted), 3);
		else
			res = ft_free_join(res, ft_substr(s, i, 1), 3);
	}
	free(s);
	cmnd->argsstr = clean_res(res, 0, 0);
	free (res);
	return (cmnd->argsstr);
}

char	**ft_split_pipex(t_cmnd *cmnd)
{
	char	**res;
	int		counter;
	int		i;
	int		j;

	res = NULL;
	counter = 0;
	i = 0;
	cmnd->argsstr = ft_spanvar(cmnd->argsstr, cmnd, 0, 0);
	j = ft_strcounter(cmnd->argsstr, counter, 0, 0);
	res = malloc(sizeof(char *) * (j + 1));
	if (res == NULL)
		return (0);
	i = 0;
	res = ft_createstrings(cmnd, res, j);
	while (i < j)
	{
		if (res[i] == NULL)
			ft_split_free(res);
		i++;
	}
	return (res);
}
