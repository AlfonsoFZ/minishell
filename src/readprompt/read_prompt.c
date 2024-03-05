/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbolano- <mbolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:43:22 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 13:33:29 by mbolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*prompt(void)
{
	return (ft_strdup("minishell>> \001\033[1;0m\002 "));
}

char	*read_prompt(t_data *dt)
{
	char	*input;
	char	*tmp;
	int		i;

	i = 0;
	input = "";
	tmp = prompt();
	if (!tmp)
		return (NULL);
	tmp = ft_free_join("\001\033[1;32m\002", tmp, 2);
	input = readline(tmp);
	if (input && *input)
		i = check_syntax(dt, &input, -1);
	if (input && *input)
		add_history(input);
	free(tmp);
	if (i != 0)
	{
		free(input);
		return ("");
	}
	return (input);
}
