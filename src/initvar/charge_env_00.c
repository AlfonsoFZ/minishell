/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_env_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbolano- <mbolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:43 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/19 13:58:58 by mbolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_charge_env_list(char **env_mtrx, t_env **env);
void	ft_add_env_list_node(char *env_str, t_env **env);
void	ft_init_new_node_values(t_env **new_node);
size_t	ft_new_node_var_name(char *env_str, t_env **new_node, char c);
void	ft_new_node_var_value(char *env_str, t_env **new_node);

void	ft_init_new_node_values(t_env **new_node)
{
	t_env	*current;

	current = *new_node;
	current->index = -1;
	current->var_name = NULL;
	current->var_value = NULL;
	current->next = NULL;
}

size_t	ft_new_node_var_name(char *env_str, t_env **new_node, char c)
{
	t_env	*current;
	size_t	i;

	i = 0;
	current = *new_node;
	while (env_str[i] && env_str[i] != c)
		i++;
	current->var_name = (char *)malloc(sizeof(char) + (i + 1));
	if (!current->var_name)
		return (0);
	i = 0;
	while (env_str[i] && env_str[i] != c)
	{
		current->var_name[i] = env_str[i];
		i++;
	}
	current->var_name[i] = '\0';
	return (i + 1);
}

void	ft_new_node_var_value(char *env_str, t_env **new_node)
{
	t_env	*current;
	size_t	i;

	i = 0;
	current = *new_node;
	while (env_str[i])
		i++;
	current->var_value = (char *)malloc(sizeof(char) + (i + 1));
	if (!current)
		return ;
	i = 0;
	while (env_str[i])
	{
		current->var_value[i] = env_str[i];
		i++;
	}
	current->var_value[i] = '\0';
}

void	ft_add_env_list_node(char *env_str, t_env **env)
{
	size_t	count;
	t_env	*new_node;
	t_env	*current;

	count = 0;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	ft_init_new_node_values(&new_node);
	count = ft_new_node_var_name(env_str, &new_node, '=');
	if (count == 0)
		return ;
	if (count < ft_strlen(env_str))
		ft_new_node_var_value(env_str + count, &new_node);
	if (*env == NULL)
		*env = new_node;
	else
	{
		current = *env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	ft_charge_env_list(char **env_mtrx, t_env **env)
{
	int	i;

	i = 0;
	while (env_mtrx[i])
	{
		ft_add_env_list_node(env_mtrx[i], env);
		i++;
	}
	ft_init_env_list_values(env);
}
