/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:34:56 by tnave             #+#    #+#             */
/*   Updated: 2021/12/20 19:48:11 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_check_access_mini(int i, t_shell *shell, char **env)
{
	t_cmd_list *tmp;

	tmp = shell->action;
	if (built_in_check(shell->action->opt, shell))
	{
		printf("cmd is built_in\n");
	}
	else
	{
	
		while (tmp)
		{
			if (!shell->opt2)
			{
				shell->opt2 = new_opt_action(tmp);
					if (!shell->opt2)
				return ;
				// print_new_opt(shell->opt2);
				parse_les_redirections(tmp, shell);
				printf("fd = %d\n", shell->fd_temp);
			}
			if (tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END)
			{
				while (shell->parse_env && shell->parse_env[i])
				{
					shell->join = ft_strjoin_three(shell->parse_env[i], "/", shell->opt2[0]);
					if (access(shell->join, F_OK) == 0)
					{
						if (tmp->type_start == TYPE_PIPE)
						{
							(void)env;
							if (pipe(shell->pfd) == -1)
								printf("Error pipe\n");				
						}
						testfork(env, shell, tmp);					
						// opt_exec_mini(env, shell, tmp);					
						// execve(shell->join, shell->opt2, env);
					}
					// else
					// {
					// 	// dup2(shell->fd, STDIN);
					// 	// built_in_check(shell->opt2, shell);
					// }
					i++;
				}
				free_split(shell->opt2);
				shell->opt2 = NULL;
				shell->fd_in = 0;
				shell->fd_out = 1;
				shell->fd_temp = -1;
			}
			i = 0;
			tmp = tmp->next;
		}
	}
}



char	**new_opt_action(t_cmd_list *action)
{
	int i;
	int j;
	t_cmd_list *tmp;
	char **temp;

	temp = NULL;
	i = 0;
	j = 0;
	tmp = action;
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
		if (tmp->type_start == TYPE_REDIR_LEFT && shell->fd_in != -1)
		{
			shell->fd_in = open(tmp->fichier, O_RDONLY);
			if (shell->fd_in < 0)
				printf("bash: %s: No such file or directory\n", tmp->fichier);
		}
		else if (tmp->type_start == TYPE_REDIR_RIGHT)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
		}
		else if (tmp->type_start == TYPE_REDIR)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
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

int	parse_env_2(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->new_env_tab[i])
	{
		if (ft_strncmp(shell->new_env_tab[i], "PATH=", 5) == 0)
		{
			shell->parse_env = ft_split(is_slash(shell->new_env_tab[i]), ':');
			return (1);
		}
		i++;
	}
	return (0);
}

int	test_execve(t_shell *shell)
{
	shell->new_env_tab = new_env_tab(shell);
	if (!shell->new_env_tab)
		return (0);
	if (parse_env_2(shell))
	{
		ft_check_access_mini(0, shell, shell->new_env_tab);
	}
	else
		printf("PATH NOT GOOD\n");

	return (0);
}