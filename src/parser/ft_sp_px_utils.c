/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_px_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:24:11 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 15:27:31 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	eval_quotes(int *in_quotes, char str, char *quote)
{
	if (*quote == '\0')
	{
		*quote = str;
		*in_quotes = !*in_quotes;
	}
	else if (*quote == str)
	{
		*quote = '\0';
		*in_quotes = !*in_quotes;
	}
}

int	ft_strcounter(char *str, int counter, int in_word, int in_quotes)
{
	char	quote;

	quote = '\0';
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			eval_quotes(&in_quotes, *str, &quote);
		if (*str == ' ' && !in_quotes)
			in_word = 0;
		else if (*str != ' ' && !in_word)
		{
			in_word = 1;
			counter++;
		}
		str++;
	}
	return (counter);
}
