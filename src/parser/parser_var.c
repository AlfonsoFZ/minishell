/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:17:41 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 20:01:37 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_special_var(t_cmnd *cmnd, char *s, int j, int dq)
{
	if (s[j] == '\0' || (s[j] == '"' && dq != 0))
		return (ft_strdup("$"));
	if (s[j] == '$' && s[j - 1] == '$')
		return (ft_itoa(cmnd->dt->ppid));
	else if (s[j] == '_' && (!ft_isalnum(s[j + 1])))
	{
		if (cmnd->dt->last_cmnd_arg)
			return (ft_strdup(cmnd->dt->last_cmnd_arg));
		else
			cmnd->dt->last_cmnd_arg = ft_strdup("0");
	}
	else if (s[j] == '?')
	{
		if (cmnd->dt->last_exit == 0)
			cmnd->dt->last_exit_str = ft_strdup("0");
		else
			cmnd->dt->last_exit_str = ft_itoa(cmnd->dt->last_exit);
		return (cmnd->dt->last_exit_str);
	}
	return (NULL);
}

static char	*ft_get_var_name(char *s, int *i, int dq)
{
	char	*res;

	(void)dq;
	res = ft_strdup("");
	*i = *i + 1;
	if (s[*i] && (ft_isalpha((int)s[*i]) || s[*i] == '_'))
	{
		while (s[*i] && ((ft_isalnum(s[*i]) && s[*i] != ' ') || s[*i] == '_'))
		{
			res = ft_free_join(res, ft_substr(s, *i, 1), 3);
			(*i)++;
		}
	}
	return (res);
}

char	*get_var_value(t_cmnd *cmnd, char *name)
{
	t_env	*tmp;

	tmp = cmnd->dt->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, name) \
			&& ft_strlen(tmp->var_name) == ft_strlen(name))
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_var(t_cmnd *cmnd, int *i, int dq, int ix)
{
	char	*name;
	char	*res;
	char	*s;

	if (cmnd->dt->cmds[ix])
		s = cmnd->dt->cmds[ix];
	else
		return (NULL);
	res = NULL;
	res = check_special_var(cmnd, s, (*i + 1), dq);
	if (res)
	{
		(*i)++;
		return (res);
	}
	name = ft_get_var_name(s, i, dq);
	if (get_var_value(cmnd, name))
		res = ft_strdup(get_var_value(cmnd, name));
	else
		res = ft_strdup("");
	free(name);
	(*i) = (*i) - 1;
	return (res);
}

char	*ft_get_var_hd(t_cmnd *cmnd, char *s, int *i, int dq)
{
	char	*name;
	char	*res;

	res = NULL;
	res = check_special_var(cmnd, s, (*i + 1), dq);
	if (res)
	{
		(*i)++;
		return (res);
	}
	name = ft_get_var_name(s, i, dq);
	if (get_var_value(cmnd, name))
		res = ft_strdup(get_var_value(cmnd, name));
	else
		res = ft_strdup("");
	free(name);
	(*i) = (*i) - 1;
	return (res);
}
