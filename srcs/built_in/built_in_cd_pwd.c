/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:11:02 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/12 11:51:15 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*convert_tild(char *str, t_shell *shell)
{
	char	*new;

	new = ft_strjoin(shell->home, &str[1]);
	return (new);
}

int	built_in_cd(t_shell *shell, char **opt)
{
	char *temp;

	temp = NULL;
	if (!opt[1])
	{
		if (!go_to_home(shell))
			ft_error_two("bash: cd: HOME not set\n", shell, 7);
		else
			parse_pwd_two(shell);
	}
	else
	{
		if (opt[1][0] == '~')
		{
			temp = opt[1];
			opt[1] = convert_tild(opt[1], shell);
			free(temp);
			temp = NULL;
		}
		if (chdir(opt[1]) == -1)
			ft_error_two(opt[1], shell, 3);
		parse_pwd_two(shell);
	}
	return (0);
}

int	built_in_pwd(t_shell *shell)
{
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
