/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:01:24 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/11 11:51:50 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_remove_var(char *var_name, t_env **env)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current && ft_strcmp(current->var_name, var_name) != 0)
	{
		previous = current;
		current = current->next;
	}
	if (current && ft_strcmp(current->var_name, var_name) == 0)
	{
		if (previous)
			previous->next = current->next;
		else
			*env = current->next;
		free(current->var_name);
		free(current->var_value);
		free(current);
	}
	return (0);
}

int	ft_unset(t_data *dt, t_cmnd *cmnd)
{
	int	i;

	i = 1;
	if (cmnd->args[1] && cmnd->args[1][0] == '-')
	{
		ft_putstr_fd("unset: options not requested in subject\n", 2);
		return (125);
	}
	else
	{
		while (cmnd->args[i])
		{
			ft_remove_var(cmnd->args[i], &dt->env_lst);
			i++;
		}
	}
	ft_index_env_lst(&dt->env_lst);
	return (0);
}
