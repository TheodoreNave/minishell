/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:25:42 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/14 15:51:51 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_pwd_two_exten(t_shell *shell, t_env *tmp, char *pwd_temp)
{
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
		tmp = tmp->next;
	}	
	return ;
}

int	parse_pwd_two(t_shell *shell)
{
	t_env	*tempo;
	t_env	*tmp;
	char	*pwd_temp;

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
	parse_pwd_two_exten(shell, tmp, pwd_temp);
	if (pwd_temp)
	{
		free(pwd_temp);
		pwd_temp = NULL;
	}
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
