/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islonglong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbolano- <mbolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:01:58 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/18 13:06:14 by mbolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_islonglong(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	ft_check_sign(str, &i, &flag);
	ft_check_zero(str, &i);
	if (ft_strlen(str + i) > 19)
		return (1);
	else if (ft_strlen(str + i) == 19)
	{
		if (flag == 1 && ft_strncmp(str + i, "9223372036854775808", 19) > 0)
			return (1);
		if (flag == 0 && ft_strncmp(str + i, "9223372036854775807", 19) > 0)
			return (1);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
