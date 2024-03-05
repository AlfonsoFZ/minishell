/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbolano- <mbolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:41:57 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/19 13:57:22 by mbolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_paths(char **env)
{
	char	*get_paths;

	get_paths = NULL;
	while (*env++)
	{
		if (ft_strnstr((const char *)*env, "PATH=", 5))
		{
			get_paths = ft_strnstr((const char *)*env, "PATH=", 5);
			return (ft_substr(get_paths, 5, ft_strlen(get_paths) - 5));
		}
	}
	return (get_paths);
}

static void	clean_pointers(char **paths, char *res, char *tmp)
{
	ft_freenull(tmp);
	ft_freenull(res);
	ft_split_free(paths);
}

char	*getpath(char *argv, char **env, int i, char *resok)
{
	char	**paths;
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = NULL;
	if (ft_strchr(argv, '/'))
		return (ft_strdup(argv));
	res = ft_free_join("/", argv, 0);
	tmp = get_paths(env);
	paths = ft_split(tmp, ':');
	while (paths[++i])
	{
		resok = ft_free_join(paths[i], res, 0);
		if (access(resok, X_OK) != 0)
			free (resok);
		else if (access(resok, X_OK) == 0)
		{
			clean_pointers(paths, res, tmp);
			return (resok);
		}
	}
	clean_pointers(paths, res, tmp);
	return (NULL);
}
