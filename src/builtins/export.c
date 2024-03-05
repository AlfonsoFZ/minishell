/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:44:50 by mbolano-          #+#    #+#             */
/*   Updated: 2024/01/11 17:07:00 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_export(t_data *dt, t_cmnd *cmnd);
int		ft_is_valid_env_var(char *str);
int		ft_is_in_env_lst(char *str, t_env *env_lst);
void	ft_update_env_var(char *str, t_env **env_lst);

int	ft_is_in_env_lst(char *str, t_env *env_lst)
{
	t_env	*current;

	current = env_lst;
	while (current != NULL)
	{
		if (ft_strncmp(current->var_name, str,
				ft_strlen(current->var_name)) == 0
			&& (str[ft_strlen(current->var_name)] == '='
				|| str[ft_strlen(current->var_name)] == '\0'))
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_is_valid_env_var(char *str)
{
	int	index;

	index = 0;
	if ((str[0] >= 0 && str[0] <= 64) || (str[0] >= 91 && str[0] <= 94)
		|| (str[0] >= 123) || (str[0] == 96))
		return (0);
	while (str[index] != '\0')
	{
		if (str[index] == '=')
			return (1);
		else if (index > 0 && ((str[index] >= 0 && str[index] <= 47)
				|| (str[index] >= 58 && str[index] <= 64)
				|| (str[index] >= 91 && str[index] <= 94)
				|| (str[index] >= 123) || (str[index] == 96)))
			return (0);
		index++;
	}
	return (1);
}

int	ft_export(t_data *dt, t_cmnd *cmnd)
{
	int	index;

	index = 0;
	if (cmnd->args[1] == NULL)
		return (ft_print_export(dt->env_lst), 0);
	while (cmnd->args[++index] != NULL)
	{
		if (ft_is_valid_env_var(cmnd->args[index]) != 0)
		{
			if (ft_is_in_env_lst(cmnd->args[index], dt->env_lst) == 0)
			{
				ft_add_env_list_node(cmnd->args[index], &(dt->env_lst));
				ft_index_env_lst(&(dt->env_lst));
			}
			else
				ft_update_env_var(cmnd->args[index], &(dt->env_lst));
		}
		else
			return (ft_err_msg("export: `", cmnd->args[index], \
				"\': not a valid identifier", 1), 1);
	}
	return (0);
}

void	ft_update_env_var(char *str, t_env **env_lst)
{
	t_env	*current;
	size_t	index;

	current = *env_lst;
	while (current != NULL)
	{
		if (ft_strncmp(current->var_name, str,
				ft_strlen(current->var_name)) == 0
			&& (str[ft_strlen(current->var_name)] == '='
				|| str[ft_strlen(current->var_name)] == '\0'))
		{
			index = ft_strlen(current->var_name);
			if (str[index] == '=')
				index++;
			free(current->var_value);
			current->var_value = ft_strdup(str + index);
			return ;
		}
		current = current->next;
	}
}
