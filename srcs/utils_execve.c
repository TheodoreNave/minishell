/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:36:35 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/12 18:54:30 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_value(t_shell *shell, t_cmd_list *tmp)
{
	if (shell->opt2)
	{
		free_split(shell->opt2);
		shell->opt2 = NULL;	
	}
	shell->opt2 = new_opt_action(tmp);
	if (!shell->opt2)
		return ;
	parse_les_redirections(tmp, shell);
	if (shell->parse_env)
	{
		free_split(shell->parse_env);
		shell->parse_env = NULL;
	}
	if (shell->join)
	{
		free(shell->join);
		shell->join = NULL;
	}
	parse_env_2(shell);
}

void	reset_value(t_shell *shell)
{
	if (shell->join)
	{
		free(shell->join);
		shell->join = NULL;
	}
	if (shell->opt2)
	{
		free_split(shell->opt2);
		shell->opt2 = NULL;	
	}
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->fd_temp = -1;
	if (shell->parse_env)
	{
		free_split(shell->parse_env);
		shell->parse_env = NULL;
	}
	if (shell->tmp_file)
	{
		unlink(shell->tmp_file);
		free(shell->tmp_file);
		shell->tmp_file = NULL;
	}
	
	return ;
}

char	**new_opt_action(t_cmd_list *action)
{
	t_cmd_list	*tmp;
	int			i;
	int			j;
	char		**temp;

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

void 	convert_dol_her(char *str, t_shell *shell, long *j)
{
	t_env	*tmp;
	int		size;
	int 	i;
	dprintf(2, "str 2 = %s\n", str);
	i = 0;
	size = ft_strlen_space(str);
	tmp = shell->environ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, str, size) == 0)
		{
			if ((tmp->var_env[size] = '='))
			{
				while (tmp->var_env[size + 1 + i])
				{
					add_to_buff_king(shell, tmp->var_env[size + 1 + i], j);
					i++;
				}
			}
			else
				add_to_buff_king(shell, 0, j);
		}
		tmp = tmp->next;
	}	
}

int	parse_dollars_heredoc(char *str, t_shell *shell, char *tmp)
{
	int i;
	long j;

	i = 0;
	j = 0;
	if (!str)
	{
		ft_error_two(tmp, shell, 8);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '$' && (!(is_whitespace(str[i + 1]))))
		{
			dprintf(2, "str 1 = %s\n", str);
			convert_dol_her(&str[i + 1], shell, &j);
			dprintf(2, "strlen = %d\n", ft_strlen_space(&str[i + 1]));
			i += ft_strlen_space(&str[i + 1]) + 1;
		}
		add_to_buff_king(shell, str[i], &j);
		i++;
	}
	return (0);
}

int 	ft_heredoc(t_shell *shell, t_cmd_list *tmp)
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

void 	parse_les_redirections(t_cmd_list *temp, t_shell *shell)
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
				printf("fd = %d\n", shell->fd_out);
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

