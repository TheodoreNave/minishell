/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exec_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:35 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/12 18:40:41 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	opt_exec_mini(char **environ, t_shell *shell, t_cmd_list *tmp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fderr(strerror(errno), NULL);
		return (0);
	}
	if (pid == 0)
	{
		if (tmp->type_start == TYPE_PIPE)
		{
			close(shell->pfd[0]);
			dup2(shell->pfd[1], STDOUT);
		}
		if (shell->fd_base > 0 && (tmp->type_end == TYPE_PIPE
				|| tmp->type_end == TYPE_END))
		{
			close(shell->pfd[1]);
			dup2(shell->fd_base, STDIN);
		}
		if (shell->fd_in > 0 )
			dup2(shell->fd_in, STDIN);
		if (shell->fd_out > 0)
			dup2(shell->fd_out, STDOUT);
		if (!built_in_check(shell->opt2, shell))
		{
			if (execve(shell->join, shell->opt2, environ) == -1)
			{
				if (access(shell->join, F_OK))
				{
					if (!ft_strchr(shell->opt2[0], '/'))
					{
						ft_putstr_fderr("bash: %s: ", shell->opt2[0]);
						ft_putstr_fderr("%s", "No such file or directory\n");
					}
					else
					{
						ft_putstr_fderr("%s: ", shell->opt2[0]);
						ft_putstr_fderr("%s", "Command Not Found\n");
					}
					clear(shell);
					exit(127);
				}
				else if (access(shell->join, R_OK | W_OK | X_OK ))
				{
					ft_putstr_fderr("bash: %s: ", shell->opt2[0]);
					ft_putstr_fderr("%s\n", strerror(errno));
					clear(shell);
					exit(126);
				}
				else
				{
					ft_putstr_fderr("bash: %s: Is a directory\n",
						shell->opt2[0]);
					clear(shell);
					exit(126);
				}
			}
		}
		clear(shell);
		exit(0);
	}
	else if (tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END)
	{
		g_global.no_ctrlc = 1;
		g_global.error_dollars = 130;
		// if (shell->fd_temp > 0)
		// 	close(shell->fd_temp);
		if (shell->fd_base > 0)
			close(shell->fd_base);
		shell->fd_base = shell->pfd[0];
		close(shell->pfd[1]);
	}
	// else
	return (pid);
}
