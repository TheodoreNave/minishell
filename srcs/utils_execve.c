/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:36:35 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/31 14:26:10 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_value(t_shell *shell, t_cmd_list *tmp)
{
	shell->opt2 = new_opt_action(tmp);
		if (!shell->opt2)
	return ;
	parse_les_redirections(tmp, shell);
	parse_env_2(shell);	
}

void	reset_value(t_shell *shell)
{
	free(shell->join);
	shell->join = NULL;
	free_split(shell->opt2);
	shell->opt2 = NULL;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->fd_temp = -1;
	return ;
}	

char	**new_opt_action(t_cmd_list *action)
{
	int i;
	int j;
	t_cmd_list *tmp;
	char **temp;

	i = 0;
	j = 0;
	tmp = action;
	temp = NULL;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->opt)
			i += ft_count_line(tmp->opt);
		if (tmp->fichier != NULL)
			i += 1;
		tmp = tmp->next;
	}
	tmp = action;
	temp = malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->opt)
		{
			while (tmp->opt[j])
			{
				temp[i] = ft_strdup(tmp->opt[j]);
				j++;
				i++;
			}
		}
		tmp = tmp->next;
		j = 0;
	}
	temp[i] = NULL;
	return (temp);
}


void 	ft_heredoc(t_shell *shell, t_cmd_list *tmp)
{
		// int i;

		// i = 0;
		// (void)tmp;
		shell->fichier_temp = tmp->fichier;
		shell->fd_temp = open(tmp->fichier, O_RDWR | O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
		static char	*buffer_doc = (char *)NULL;
		while (1)
		{
			// shell->prompt_heredoc = 1;
			buffer_doc = readline("> ");
			if (!ft_strncmp(tmp->fichier, buffer_doc, ft_strlen(tmp->fichier)))
			{
				// shell->prompt_heredoc = 0;
				printf("Ca fonctionne\n");
				// rl_on_new_line();
				rl_replace_line("", 0);
				printf("break\n");
				break ;
			}
			write(shell->fd_temp, buffer_doc, ft_strlen(buffer_doc));
			write(shell->fd_temp, "\n", 1);
			// rl_on_new_line();
			rl_replace_line("", 0);
		}
		printf("after break\n");
		shell->fd_temp = open(tmp->fichier, O_RDONLY);
		free(buffer_doc);
		// return (shell->fd_temp);
		
}

void 	parse_les_redirections(t_cmd_list *temp, t_shell *shell)
{
	t_cmd_list *tmp;

	tmp = temp;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->type_start == TYPE_REDIR_LEFT)
		{
			shell->fd_in = open(tmp->fichier, O_RDONLY);
			if (shell->fd_in < 0)
			{
				printf("bash: %s: No such file or directory\n", tmp->fichier);
				shell->pipe = -1;
			}
			shell->fd_out = -1;
		}
		else if (tmp->type_start == TYPE_REDIR_RIGHT)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
			shell->fd_in = -1;
		}
		else if (tmp->type_start == TYPE_REDIR)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
			shell->fd_in = -1;
		}
		else if (tmp->type_start == TYPE_HEREDOC && tmp->fichier != NULL)	// ADD cat exception
		{
			ft_heredoc(shell, tmp);
			
			// if (ft_strncmp(shell->opt2, "cat", 3)
			// ft_heredoc_cat()
		}
		tmp = tmp->next;
	}
}

