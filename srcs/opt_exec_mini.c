/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exec_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:35 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/24 19:00:36 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	opt_exec_mini(char **environ, t_shell *shell, t_cmd_list *tmp)
{
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
		if (shell->fd_in > 0 )
			dup2(shell->fd_in, STDIN);
		if (shell->fd_out > 0)
			dup2(shell->fd_out, STDOUT);
		if (!built_in_check(shell->opt2, shell))
		{
			if (execve(shell->join, shell->opt2, environ) == -1)
			{
				if (access(shell->join, F_OK))
					write(2, "bash: command not found\n", 25);
				else
					perror("bash");
			}
		}
		// dprintf(2, "JE SUIS LA2\n");
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

pid_t	opt_exec_mini_without_pipe(char **environ, t_shell *shell, t_cmd_list *tmp)
{
	(void)tmp;
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		printf("Error PID\n");
	if (pid == 0)
	{	

		if (execve(shell->join, shell->opt2, environ) == -1)
		{
			if (access(shell->join, F_OK))
			{
				write(2, "bash: command not found\n", 25);
				perror("bash");				
				exit(127);
			}
			// else
				// perror("bash");
		}
		dprintf(2, "JE SUIS LA3");
	}
	return (pid);
}