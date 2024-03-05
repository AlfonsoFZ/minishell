/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:40:24 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/17 16:56:45 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_export(t_env *env_lst);

void	ft_print_export(t_env *env_lst)
{
	t_env	*current;
	int		index;

	current = env_lst;
	index = 0;
	while (index < ft_lstlen(&env_lst))
	{
		current = env_lst;
		while (current->index != index)
			current = current->next;
		if (ft_strcmp(current->var_name, "_") != 0)
		{
			printf(YELLOW "declare -x " COLOR_RESET);
			printf(RED "%s" COLOR_RESET, current->var_name);
			if (current->var_value != NULL && *current->var_value != '\0')
			{
				printf(YELLOW "=\"" COLOR_RESET);
				printf(PURPLE "%s" COLOR_RESET, current->var_value);
				printf(YELLOW "\"" COLOR_RESET);
			}
			printf("\n");
		}
		index++;
	}
}
