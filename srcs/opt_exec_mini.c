/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exec_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:40:35 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/20 20:02:25 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	opt_exec_mini(char **environ, t_shell *shell, t_cmd_list *tmp)
{
	(void)tmp;
	(void)shell;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		printf("Error PID\n");
	if (pid == 0)
	{
		// printf("tmp = %d\n", tmp->type_start);
		// if (shell->fd_in)
		// 	dup2(shell->fd_in, STDIN);
		// else
		// 	dup2(shell->pfd[STDIN], STDIN);
		// if (shell->fd_out)
		// 	dup2(shell->fd_out, STDOUT);
		// else
		// 	dup2(shell->pfd[STDOUT], STDOUT);
		
		printf("TEST\n");
		execve(shell->join, shell->opt2, environ);
		// exit(127);
	}
	else													// < fichier > fichier 2
		child_mini(pid, shell, tmp);
	printf("TEST\n");
}

void	child_mini(pid_t pid, t_shell *shell, t_cmd_list *tmp)
{
	(void)tmp;
	(void)shell;
	(void)pid;
	waitpid(pid, NULL, 0);
	// if (tmp->prev)
	// 	close(shell->pfd[STDIN]);
	// if (tmp->next)
	// 	close(shell->pfd[STDOUT]);
	// if (!tmp->next)
	printf("TEST2\n");
		return;
		// exit(1); //clear lst...
}

void	testfork(char **environ, t_shell *shell, t_cmd_list *tmp)
{
	// pid_t	pid;

	// pid = fork();
	// if (pid < 0)
	// 	printf("Error PID\n");
	// if (pid == 0)
	// {
		opt_exec_mini(environ, shell, tmp);
	// }
	// else
	// {
	// 	waitpid(pid, NULL, 0);
	// }
	// printf("OKOKOK\n");
}