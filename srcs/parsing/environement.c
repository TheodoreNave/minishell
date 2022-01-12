/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:25:42 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/12 12:07:03 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_pwd_two(t_shell *shell)
{
	t_env	*tempo;
	t_env	*tmp;
	char	*pwd_temp;
	int		i;

	i = 0;
	pwd_temp = NULL;
	tmp = shell->environ;
	tempo = shell->environ;
	while (tempo)
	{
		if (ft_strncmp(tempo->var_env, "PWD=", 4) == 0)
		{
			pwd_temp = ft_strjoin("OLD", tempo->var_env);
		}
		tempo = tempo->next;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, "OLDPWD=", 7) == 0)
		{
			if (shell->on == 0)
			{
				free(tmp->var_env);
				tmp->var_env = ft_strdup(pwd_temp);
			}
		}
		if (ft_strncmp(tmp->var_env, "PWD=", 4) == 0)
		{
			if (shell->on == 0)
			{
				free(tmp->var_env);
				tmp->var_env = ft_strjoin("PWD=", getcwd(shell->buff_pwd,
							sizeof(shell->buff_pwd)));
			}
		}
		i++;
		tmp = tmp->next;
	}
	if (pwd_temp)
		free(pwd_temp);
	return (0);
}

int	parse_pwd(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->environ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, "PWD=", 4) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("PWD=", getcwd(shell->buff_pwd,
						sizeof(shell->buff_pwd)));
		}
		if (ft_strncmp(tmp->var_env, "OLDPWD=", 7) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("OLDPWD=", getcwd(shell->buff_pwd,
						sizeof(shell->buff_pwd)));
		}
		if (ft_strncmp(tmp->var_env, "_=", 2) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strdup("_=/usr/bin/env");
		}
		tmp = tmp->next;
	}
	return (0);
}

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

char	**new_env_tab(t_shell *shell)
{
	t_env	*tmp;
	char	**tab;
	int		size;
	int		i;

	tmp = shell->environ;
	i = 0;
	size = count_env_lst(tmp);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->var_env);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}
