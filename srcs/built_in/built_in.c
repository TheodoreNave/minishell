/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:44:39 by tnave             #+#    #+#             */
/*   Updated: 2021/12/08 20:31:23 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <linux/limits.h>

int	built_in_exit(t_shell *shell)
{
	(void)shell;
	//free ALL
	printf("exit\n");
	exit(0);
}

int		built_in_check(char **env, char **built_in, t_shell *shell)
{
	(void)env;
	if (!strcmp(built_in[0], "cd"))
		built_in_cd(shell, built_in);
	else if (!strcmp(built_in[0], "pwd"))
		built_in_pwd(shell);
	else if (!strcmp(built_in[0], "env"))
		print_env_lst(shell->environ);
	else if (!strncmp(built_in[0], "unset", 5))
		built_in_unset(shell, built_in);
	else if (!strncmp(built_in[0], "export", 6))
		built_in_export(built_in, shell->environ, shell);
	else
		return (0);
	// else if (strncmp(built_in[0], "exit", 4))
	// 	built_in_exit(shell);
	// if (strncmp(built_in[0], "echo", 4))
	// 	built_in_echo();
	return (1);

// int	is_built_in(char *cmd)
// {
// 	if (!strcmp(cmd, "cd"))
// 		return (1);
// 	else if (!strcmp(cmd, "pwd"))
// 		return (1);
// 	else if (!strncmp(cmd, "env", 3))
// 		return (1);
// 	else if (!strncmp(cmd, "export", 6))
// 		return (1);
// 	else if (!strncmp(cmd, "unset", 5))
// 		return (1);
// 	// else if (!strncmp(cmd, "exit", 4))
// 	// 	return (1);
// 	// else if (!strncmp(cmd, "echo", 4))
// 	// 	return (1);
// 	else
// 		return (0);
// }
}
