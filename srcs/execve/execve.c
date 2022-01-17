/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:34:56 by tnave             #+#    #+#             */
/*   Updated: 2022/01/17 14:36:23 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_pipe(t_shell *shell)
{
	if (pipe(shell->pfd) == -1)
	{
		write(2, "bash: Error pipe\n", 18);
		g_global.error_dollars = 1;
	}
}

void	check_access_mini_ext(t_shell *shell, t_cmd_list *tmp, char **env)
{
	if (!shell->opt2)
		init_value(shell, tmp);
	if ((tmp->type_end == TYPE_END) && shell->pipe == 0
		&& (built_in_check_2(shell->opt2, shell)))
	{
		shell->pipe = -1;
		reset_value(shell);
	}
	if ((tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END)
		&& shell->pipe != -1)
	{
		shell->j += 1;
		shell->pipe = 1;
		check_pipe(shell);
		shell->last_pid = opt_exec_mini(env, shell, tmp);
		reset_value(shell);
	}
	if ((tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END)
		&& shell->pipe == -1)
		reset_value(shell);
	return ;
}

void	ft_check_access_mini(int i, t_shell *shell, char **env)
{
	t_cmd_list	*tmp;
	int			ret;

	ret = 0;
	shell->j = 0;
	tmp = shell->action;
	while (tmp)
	{
		check_access_mini_ext(shell, tmp, env);
		tmp = tmp->next;
	}
	shell->pipe = 0;
	if (shell->fd_base > 0)
		close(shell->fd_base);
	i = 0;
	while (i < shell->j)
	{
		if (waitpid(-1, &ret, 0) == shell->last_pid)
		{
			if (WIFEXITED(ret))
				g_global.error_dollars = WEXITSTATUS(ret);
		}
		i++;
	}
}

int	test_execve(t_shell *shell)
{
	if (shell->new_env_tab)
		free_split(shell->new_env_tab);
	shell->new_env_tab = new_env_tab(shell);
	if (!shell->new_env_tab)
		return (0);
	ft_check_access_mini(0, shell, shell->new_env_tab);
	return (0);
}
