/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:11:02 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/13 17:23:57 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		built_in_cd(t_shell *shell, char **opt)
{
	// Strerror ?
	if (!opt[1])
	{
		if (chdir(getenv("HOME")) == -1)
			ft_error_two("chdir()", shell, 1);
		parse_pwd_two(shell);
	}
	else
	{
		if (chdir(opt[1]) == -1)
			ft_error_two(opt[1], shell, 3);
		parse_pwd_two(shell);
	}
	return (0);
}

int		built_in_pwd(t_shell *shell)
{
	// Strerror
	t_env	*tmp;
	char	current[BUFF_MAX];

	tmp = shell->environ;
	if (getcwd(current, sizeof(current)))
		printf("%s\n", current);
	else
	{
		shell->on = 1;
		while (tmp)
		{
			if (ft_strncmp(tmp->var_env, "PWD=", 4) == 0)
			{
				printf("%s\n", &tmp->var_env[4]);
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
