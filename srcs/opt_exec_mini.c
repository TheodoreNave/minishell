/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exec_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:35 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/05 14:22:44 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	opt_exec_mini(char **environ, t_shell *shell, t_cmd_list *tmp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("Error PID\n"); // Error message 127
		shell->error_dol = 127;
	}
	if (pid == 0)
	{
		if (tmp->type_start == TYPE_PIPE )
		{
			close(shell->pfd[0]);
			dup2(shell->pfd[1], STDOUT);
		}
		if (shell->fd_base > 0 && (tmp->type_end == TYPE_PIPE || tmp->type_end == TYPE_END))
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
					write(2, "bash2: command not found\n", 25); // Error Message 127
					shell->error_dol = 127;
				}
				// else
				// 	perror("bash3");
			}
		}
		exit(127);
	}
	else if(tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END)
	{
		if (shell->fd_base > 0)
			close(shell->fd_base);
		shell->fd_base = shell->pfd[0];
		close(shell->pfd[1]);
	}
	return (pid);
}