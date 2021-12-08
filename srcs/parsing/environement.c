/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:25:42 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/08 19:52:37 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 	parse_pwd_two(t_shell *shell)
{
	int i;
	t_env *tmp;
	t_env *tempo;
	char *pwd_temp;
	
	pwd_temp = NULL;
	tmp = shell->environ;
	tempo = shell->environ;
	i = 0;
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
			free(tmp->var_env);
			tmp->var_env = ft_strdup(pwd_temp);
		}
		if (ft_strncmp(tmp->var_env, "PWD=", 4) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("PWD=", getcwd(shell->buff_pwd, sizeof(shell->buff_pwd)));
		}
		i++;
		tmp = tmp->next;
	}
	free(pwd_temp);
	return (0);
}

int 	parse_pwd(t_shell *shell)
{
	int i;
	t_env *tmp;

	tmp = shell->environ;
	i = 0;
	
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, "PWD=", 4) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("PWD=", getcwd(shell->buff_pwd, sizeof(shell->buff_pwd)));
		}
		if (ft_strncmp(tmp->var_env, "OLDPWD=", 7) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("OLDPWD=", getcwd(shell->buff_pwd, sizeof(shell->buff_pwd)));
		}
		tmp = tmp->next;
	}
	return (0);
}

int		stock_env(char **env, t_shell *shell)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (env[i])
	{
		ft_lstadd_back_env(&shell->environ, ft_lstnew_env(env[i]));
		i++;
	}
	parse_pwd(shell);
	return (0);
}
