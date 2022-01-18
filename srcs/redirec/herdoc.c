/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:36:35 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/18 16:47:09 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_heredoc_write(t_shell *shell)
{
	write(shell->fd_in, shell->buffer_king, ft_strlen(shell->buffer_king));
	write(shell->fd_in, "\n", 1);
	clear_buffer_king(shell);
	return ;
}

void	ft_heredoc_init(t_shell *shell, t_cmd_list *tmp)
{
	if (shell->tmp_file)
	{
		unlink(shell->tmp_file);
		free(shell->tmp_file);
		shell->tmp_file = NULL;
	}
	shell->tmp_file = ft_strjoin(".", tmp->fichier);
	shell->fd_in = open(shell->tmp_file, O_WRONLY | O_TRUNC
			| O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
	return ;
}

int	ft_heredoc(t_shell *shell, t_cmd_list *tmp)
{
	static char	*buffer_doc;

	buffer_doc = (char *) NULL;
	ft_heredoc_init(shell, tmp);
	while (1)
	{
		buffer_doc = readline("> ");
		if (buffer_doc
			&& !ft_strncmp(tmp->fichier, buffer_doc, ft_strlen(tmp->fichier)))
		{
			g_global.read_here_doc = 1;
			break ;
		}
		if (parse_dollars_heredoc(buffer_doc, shell, tmp->fichier))
		{
			unlink(shell->tmp_file);
			free(shell->tmp_file);
			shell->tmp_file = NULL;
			return (0);
		}
		ft_heredoc_write(shell);
	}
	close(shell->fd_in);
	shell->fd_in = open(shell->tmp_file, O_RDONLY);
	return (0);
}
