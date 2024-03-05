/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:25 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/17 17:34:06 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_env_list(t_env *env);

void	ft_print_env_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->var_value)
		{
			ft_putstr_fd(current->var_name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(current->var_value, 1);
		}
		current = current->next;
	}
}
