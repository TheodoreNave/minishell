/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:36:35 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/14 18:35:00 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc(t_shell *shell, t_cmd_list *tmp)
{
	static char	*buffer_doc;

	buffer_doc = (char *)NULL;
	if (shell->tmp_file)
	{
		unlink(shell->tmp_file);
		free(shell->tmp_file);
		shell->tmp_file = NULL;
	}
	shell->tmp_file = ft_strjoin(".", tmp->fichier);
	shell->fd_in = open(shell->tmp_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
	while (1)
	{
		buffer_doc = readline("> ");
		if (buffer_doc && !ft_strncmp(tmp->fichier, buffer_doc, ft_strlen(tmp->fichier)))
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
		write(shell->fd_in, shell->buffer_king, ft_strlen(shell->buffer_king));
		write(shell->fd_in, "\n", 1);
		clear_buffer_king(shell);
	}
	close(shell->fd_in);
	shell->fd_in = open(shell->tmp_file, O_RDONLY);
	return (0);
}

void	parse_les_redirections(t_cmd_list *temp, t_shell *shell)
{
	t_cmd_list	*tmp;

	tmp = temp;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->type_start == TYPE_REDIR_LEFT)
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
		}
		else if (tmp->type_start == TYPE_REDIR_RIGHT)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
			if (shell->fd_out < 0)
			{
				ft_putstr_fderr("bash: %s: No such file or directory\n", tmp->fichier);
				g_global.error_dollars = 1;
				close(shell->fd_out);
			}
			else
				shell->fd_in = -1;
		}
		else if (tmp->type_start == TYPE_REDIR)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
			if (shell->fd_out < 0)
			{
				ft_putstr_fderr("bash: %s: No such file or directory\n", tmp->fichier);
				g_global.error_dollars = 1;
				close(shell->fd_out);
			}
			else
				shell->fd_in = -1;
		}
		else if (tmp->type_start == TYPE_HEREDOC && tmp->fichier != NULL)
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
		}
		tmp = tmp->next;
	}
}

