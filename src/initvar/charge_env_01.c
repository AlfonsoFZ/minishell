/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_env_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbolano- <mbolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 07:59:25 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/19 14:00:30 by mbolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_charge_env_mtrx_from_envp(char **env, char ***env_mtrx);
void	ft_pull_values_over_mtrx(t_env **env_lst, char ***env_mtrx);
void	ft_charge_env_mtrx_from_lst(t_env **env_lst, char ***env_mtrx);
void	ft_index_env_lst(t_env **env_lst);

void	ft_index_env_lst(t_env **env_lst)
{
	t_env	*current;
	t_env	*count;
	int		index;

	index = -1;
	ft_init_env_vars_index(env_lst);
	while (++index < ft_lstlen(env_lst))
	{
		count = *env_lst;
		current = *env_lst;
		while (current->index != -1 && current->next)
			current = current->next;
		while (count)
		{
			if (ft_strcmp(count->var_name, current->var_name) < 0
				&& count->index == -1)
				current = count;
			count = count->next;
		}
		current->index = index;
	}
}

void	ft_charge_env_mtrx_from_envp(char **env, char ***env_mtrx)
{
	int	i;
	int	j;

	*env_mtrx = (char **)malloc(sizeof(char *) * (ft_mtrxlen(env) + 1));
	if (!(*env_mtrx))
		return ;
	i = 0;
	while (env[i])
	{
		(*env_mtrx)[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!(*env_mtrx)[i])
		{
			ft_free_matrix(*env_mtrx);
			return ;
		}
		j = 0;
		while (env[i][j])
		{
			(*env_mtrx)[i][j] = env[i][j];
			j++;
		}
		(*env_mtrx)[i][j] = '\0';
		i++;
	}
	(*env_mtrx)[i] = NULL;
}

int	ft_lst_value_len(t_env **env_lst)
{
	int		i;
	t_env	*current;

	i = 0;
	current = *env_lst;
	while (current)
	{
		if (current->var_value)
			i++;
		current = current->next;
	}
	return (i);
}

void	ft_pull_values_over_mtrx(t_env **env_lst, char ***env_mtrx)
{
	t_env	*current;
	int		i;
	size_t	len;

	i = 0;
	current = *env_lst;
	while (current)
	{
		if (current->var_value)
		{
			len = ft_strlen(current->var_name)
				+ ft_strlen(current->var_value) + 2;
			(*env_mtrx)[i] = (char *)malloc(sizeof(char) * len);
			if (!(*env_mtrx)[i])
				return (ft_free_matrix(*env_mtrx));
			ft_strlcpy((*env_mtrx)[i], current->var_name,
				ft_strlen(current->var_name) + 2);
			ft_strlcat((*env_mtrx)[i], "=", (ft_strlen(current->var_name) + 2));
			ft_strlcat((*env_mtrx)[i], current->var_value,
				ft_strlen((*env_mtrx)[i]) + ft_strlen(current->var_value) + 1);
			i++;
		}
		current = current->next;
	}
	(*env_mtrx)[i] = NULL;
}

void	ft_charge_env_mtrx_from_lst(t_env **env_lst, char ***env_mtrx)
{
	*env_mtrx = (char **)malloc(sizeof(char *)
			* (ft_lst_value_len(env_lst) + 1));
	if (!(*env_mtrx))
		return ;
	ft_pull_values_over_mtrx(env_lst, env_mtrx);
}
