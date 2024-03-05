/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:05:32 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/05 13:31:41 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lstlen(t_env **env_lst);

int	ft_lstlen(t_env **env_lst)
{
	int		i;
	t_env	*current;

	i = 0;
	current = *env_lst;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
