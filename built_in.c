/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:44:39 by tnave             #+#    #+#             */
/*   Updated: 2021/12/07 14:50:24 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <linux/limits.h>

int		built_in_cd(t_shell *shell, char *path)
{
	if (chdir(path) == -1)
		ft_error_two("chdir()", shell, 1);
	return (0);
}

int		built_in_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int		built_in_pwd(t_shell *shell)
{
	char	current[PATH_MAX];

	if (getcwd(current, sizeof(current)))
		printf("%s\n", current);
	else
		ft_error_two("getcurrent()", shell, 1);
	return (0);
}

int	is_built_in(char *cmd)
{
	printf("cmd = [%s]\n", cmd);
	printf("**********************\n");
	if (!strcmp(cmd, "cd"))
	{
		printf("cd est bon\n");
		return (1);
	}
	else if (!strcmp(cmd, "pwd"))
		return (1);
	else if (!strncmp(cmd, "env", 3))
		return (1);
	// else if (strncmp(cmd, "echo", 4))
	// 	return (1);
	// else if (strncmp(cmd, "export", 6))
	// 	return (1);
	// else if (strncmp(cmd, "unset", 5))
	// 	return (1);
	// else if (strncmp(cmd, "exit", 4))
	// 	return (1);
	else
		return (0);
}


int		built_in_check(char **env, char **built_in, t_shell *shell)
{
	// printf("built_in[0] = %s\n", built_in);
	if (!strcmp(built_in[0], "cd"))
	{
		if (!built_in[1])
		{
			if (chdir(getenv("HOME")) == -1)
				ft_error_two("chdir()", shell, 1);
		}
		else
			built_in_cd(shell, built_in[1]);
	}
	else if (!strcmp(built_in[0], "pwd"))
		built_in_pwd(shell);
	else if (!strcmp(built_in[0], "env"))
		built_in_env(env);
	// if (strncmp(built_in[0], "echo", 4))
	// 	built_in_echo();
	// else if (strncmp(built_in[0], "export", 6))
	// 	built_in_export();
	// else if (strncmp(built_in[0], "unset", 5))
	// 	built_in_unset();
	// else if (strncmp(built_in[0], "exit", 4))
	// 	built_in_exit();
	return (1);
}