/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exec_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:35 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/21 19:02:50 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	opt_exec_mini(char **environ, t_shell *shell, t_cmd_list *tmp)
{
	(void)tmp;
	(void)shell;
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		printf("Error PID\n");
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
		if (shell->fd_out > 0)
			dup2(shell->fd_out, STDOUT);
		execve(shell->join, shell->opt2, environ);
		// exit(127);
	}
	else if(tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END)
	{
		// if (shell->fd_out > 0)
			// close(shell->fd_out);
		if (shell->fd_base > 0)
			close(shell->fd_base);
		
		
		shell->fd_base = shell->pfd[0];
		close(shell->pfd[1]);
		//wait(NULL);
		// dup2(shell->pfd[0], STDIN);	
	}
	return (pid);
		// child_mini(pid, shell, tmp);
}

// void	child_mini(pid_t pid, t_shell *shell, t_cmd_list *tmp)
// {
// 	(void)tmp;
// 	(void)shell;
// 	(void)pid;
// 	waitpid(pid, NULL, 0);
// 	// if (tmp->prev)
// 		close(shell->pfd[STDIN]);
// 	// if (tmp->next)
// 		close(shell->pfd[STDOUT]);
// 	// if (!tmp->next)
// 	return;
// }
