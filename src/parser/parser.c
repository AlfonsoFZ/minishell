/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:17:53 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 13:50:06 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser(t_data *dt)
{
	dt->cmds = ft_split_pipes(dt);
	if (!dt->cmds)
		return (1);
	if (parse_cmd(dt, dt->cmds))
		return (1);
	return (0);
}
