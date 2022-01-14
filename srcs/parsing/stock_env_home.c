/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_env_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:37:46 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/14 15:39:26 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_to_home(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->environ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, "HOME=", 5) == 0)
		{
			chdir(&tmp->var_env[5]);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	stock_home(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->environ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, "HOME=", 5) == 0)
		{
			shell->home = ft_strdup(&tmp->var_env[5]);
			return ;
		}
		tmp = tmp->next;
	}
}

int	stock_env(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		ft_lstadd_back_env(&shell->environ, ft_lstnew_env(env[i]));
		i++;
	}
	parse_pwd(shell);
	stock_home(shell);
	return (1);
}
