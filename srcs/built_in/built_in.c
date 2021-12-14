/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:44:39 by tnave             #+#    #+#             */
/*   Updated: 2021/12/14 12:22:40 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		built_in_check(char **built_in, t_shell *shell)
{
	if (!strcmp(built_in[0], "cd"))
		built_in_cd(shell, built_in);
	else if (!strcmp(built_in[0], "pwd"))
		built_in_pwd(shell);
	else if (!strcmp(built_in[0], "env"))
		print_env_lst(shell->environ, 1);
	else if (!strncmp(built_in[0], "unset", 5))
		built_in_unset(shell, built_in);
	else if (!strncmp(built_in[0], "export", 6))
		built_in_export(built_in, shell->environ, shell);
	else if (!strncmp(built_in[0], "echo", 4))
	{
		if (!strncmp(built_in[1], "-n", 3))
			built_in_echo_n(&built_in[2]);
		else
			built_in_echo(&built_in[1]);
	}
	else if (!strncmp(built_in[0], "exit", 4))
		built_in_exit(shell);
	else
		return (0);
	return (1);
}

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
	// else if (!strncmp(cmd, "exit", 4))
	// 	return (1);
	// else if (!strncmp(cmd, "echo", 4))
	// 	return (1);
// 	else
// 		return (0);
// }
