/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_env_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbolano- <mbolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:19:39 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/19 13:57:51 by mbolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_init_env_vars_index(t_env **env_lst);
void	ft_init_env_list_values(t_env **env);

void	ft_init_env_vars_index(t_env **env_lst)
{
	t_env	*current;

	current = *env_lst;
	while (current)
	{
		current->index = -1;
		current = current->next;
	}
}

char	*get_value(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, name) \
			&& ft_strlen(tmp->var_name) == ft_strlen(name))
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	set_shlvl(t_env **env)
{
	char	*temp;

	if (ft_is_in_env_lst("SHLVL", *env) == 0)
		ft_add_env_list_node("SHLVL=1", env);
	else
	{
		temp = ft_itoa(ft_atoi(get_value(env, "SHLVL")) + 1);
		ft_update_var("SHLVL", temp, env);
		free(temp);
	}
}

static void	set_pwd(t_env **env)
{
	char	*temp;

	if (ft_is_in_env_lst("PWD", *env) == 0)
	{
		temp = getcwd(NULL, 0);
		temp = ft_free_join("PWD=", temp, 2);
		ft_add_env_list_node(temp, env);
		free(temp);
	}
}

void	ft_init_env_list_values(t_env **env)
{
	t_env	*current;

	set_shlvl(env);
	set_pwd(env);
	current = *env;
	while (current && ft_strcmp(current->var_name, "OLDPWD") != 0)
		current = current->next;
	if (current && ft_strcmp(current->var_name, "OLDPWD") == 0)
	{
		free(current->var_value);
		current->var_value = NULL;
	}
	else if (!current)
		ft_add_env_list_node("OLDPWD", env);
	current = *env;
	while (ft_strcmp(current->var_name, "_") != 0 && current)
		current = current->next;
	free(current->var_value);
	current->var_value = ft_strdup("true");
}
