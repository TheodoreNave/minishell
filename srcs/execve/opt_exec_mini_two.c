/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exec_mini_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:47:40 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/18 17:22:35 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_error(t_shell *shell)
{
	if (access(shell->join, F_OK))
		exec_error_one(shell);
	else if (access(shell->join, R_OK | W_OK | X_OK))
		exec_error_two(shell);
	else
		exec_error_three(shell);
	return ;
}

void	exec_error_one(t_shell *shell)
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
	clear_end(shell);
	exit(127);
}

void	exec_error_two(t_shell *shell)
{
	ft_putstr_fderr("bash: %s: ", shell->opt2[0]);
	ft_putstr_fderr("%s\n", strerror(errno));
	clear_end(shell);
	exit(126);
}

void	exec_error_three(t_shell *shell)
{
	ft_putstr_fderr("bash: %s: Is a directory\n", shell->opt2[0]);
	clear_end(shell);
	exit(126);
}

int	exec_error_pid(void)
{
	ft_putstr_fderr(strerror(errno), NULL);
	return (0);
}
