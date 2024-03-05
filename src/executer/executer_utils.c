/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:56:16 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/21 17:16:42 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (-1);
	if (S_ISDIR(statbuf.st_mode))
		return (1);
	if (!(statbuf.st_mode & S_IXUSR))
		return (2);
	return (0);
}

int	ft_check_free(t_data *dt, char *str)
{
	if (ft_strchr(str, '/') && is_directory(str) == -1)
	{
		dt->error = ft_err_msg(str, ": ", "No such file or directory", 127);
		exit (dt->error);
	}
	else if (ft_strchr(str, '/') && is_directory(str) == 1)
	{
		dt->error = ft_err_msg(str, ": ", "is a directory", 126);
		exit (dt->error);
	}
	else if (ft_strchr(str, '/') && is_directory(str) == 2)
	{
		dt->error = ft_err_msg(str, ": ", "Permission denied", 126);
		exit (dt->error);
	}
	else
	{
		errno = 127;
		dt->error = ft_err_msg(str, ": ", ERROR_CMD, errno);
		exit (dt->error);
	}
	return (dt->error);
}

char	*get_last_arg(t_data *dt)
{
	int	i;

	i = 0;
	while (dt->cmnd[0]->args[i] != NULL)
		i++;
	if (i > 0)
		return (dt->cmnd[0]->args[i - 1]);
	return (NULL);
}
