/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:22:55 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/17 13:53:17 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_left(t_cmd_list *tmp, t_shell *shell)
{
	shell->fd_in = open(tmp->fichier, O_RDONLY);
	if (shell->fd_in < 0)
	{
		ft_putstr_fderr("bash: %s: No such file or directory\n", tmp->fichier);
		g_global.error_dollars = 1;
		shell->pipe = -1;
		close(shell->fd_in);
	}
	else
		shell->fd_out = -1;
	return ;
}

void	redir_right(t_cmd_list *tmp, t_shell *shell)
{
	shell->fd_out = open(tmp->fichier, O_WRONLY
			| O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
	if (shell->fd_out < 0)
	{
		ft_putstr_fderr("bash: %s: No such file or directory\n", tmp->fichier);
		g_global.error_dollars = 1;
		close(shell->fd_out);
	}
	else
		shell->fd_in = -1;
	return ;
}

void	double_redir_right(t_cmd_list *tmp, t_shell *shell)
{
	shell->fd_out = open(tmp->fichier, O_WRONLY
			| O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
	if (shell->fd_out < 0)
	{
		ft_putstr_fderr("bash: %s: No such file or directory\n", tmp->fichier);
		g_global.error_dollars = 1;
		close(shell->fd_out);
	}
	else
		shell->fd_in = -1;
	return ;
}

void	redir_herdoc(t_cmd_list *tmp, t_shell *shell)
{
	ft_heredoc(shell, tmp);
	if (shell->fd_in < 0)
	{
		ft_putstr_fderr("bash: %s: No such file or directory\n", tmp->fichier);
		g_global.error_dollars = 1;
		shell->pipe = -1;
		close(shell->fd_in);
	}
	else
		shell->fd_out = -1;
	return ;
}

void	parse_les_redirections(t_cmd_list *temp, t_shell *shell)
{
	t_cmd_list	*tmp;

	tmp = temp;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->type_start == TYPE_REDIR_LEFT)
			redir_left(tmp, shell);
		else if (tmp->type_start == TYPE_REDIR_RIGHT)
			redir_right(tmp, shell);
		else if (tmp->type_start == TYPE_REDIR)
			double_redir_right(tmp, shell);
		else if (tmp->type_start == TYPE_HEREDOC && tmp->fichier != NULL)
			redir_herdoc(tmp, shell);
		tmp = tmp->next;
	}
}
