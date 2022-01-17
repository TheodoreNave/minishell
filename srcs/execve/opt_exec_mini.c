/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exec_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:35 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/17 15:00:29 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_fd(t_shell *shell, t_cmd_list *tmp)
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
	if (shell->fd_in > 0)
		dup2(shell->fd_in, STDIN);
	if (shell->fd_out > 0)
		dup2(shell->fd_out, STDOUT);
	return ;
}

void	ft_pid_father(t_shell *shell)
{
	g_global.no_ctrlc = 1;
	g_global.error_dollars = 130;
	if (shell->fd_base > 0)
		close(shell->fd_base);
	shell->fd_base = shell->pfd[0];
	close(shell->pfd[1]);
	return ;
}

pid_t	opt_exec_mini(char **environ, t_shell *shell, t_cmd_list *tmp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (exec_error_pid());
	if (pid == 0)
	{
		init_fd(shell, tmp);
		if (!built_in_check(shell->opt2, shell))
		{
			if (execve(shell->join, shell->opt2, environ) == -1)
				exec_error(shell);
		}
		clear_end(shell);
		exit(0);
	}
	else if (tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END)
		ft_pid_father(shell);
	return (pid);
}
