/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:49:56 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/05 12:32:32 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_env_lst(t_env **vars);

void	ft_free_env_lst(t_env **vars)
{
	t_env	*current;
	t_env	*next;

	if (!vars || !*vars)
		return ;
	current = *vars;
	while (current)
	{
		next = current->next;
		if (current->var_name)
			free(current->var_name);
		if (current->var_value)
			free(current->var_value);
		free(current);
		current = next;
	}
}
