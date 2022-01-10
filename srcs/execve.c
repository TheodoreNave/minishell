/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:34:56 by tnave             #+#    #+#             */
/*   Updated: 2022/01/10 15:44:32 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_check_access_mini(int i, t_shell *shell, char **env)
{
	int j = 0;
	pid_t last_pid;
	t_cmd_list *tmp;

	tmp = shell->action;
	while (tmp)
	{
		if (!shell->opt2)
		{
			init_value(shell, tmp);
		}
		if ((tmp->type_end == TYPE_END) && shell->pipe == 0 && (built_in_check_2(shell->opt2, shell)))
		{
			shell->pipe = -1;
			reset_value(shell);
		}
		if ((tmp->type_start == TYPE_PIPE || tmp->type_end == TYPE_END) && shell->pipe != -1)
		{
			j += 1;
			shell->pipe = 1;
			if (pipe(shell->pfd) == -1)
			{
				printf("Error pipe\n"); // exit Message 1 ?
				g_global.error_dollars = 1; // Sure ??
			}
			last_pid = opt_exec_mini(env, shell, tmp);
			reset_value(shell);
		}
		tmp = tmp->next;
	}
	shell->pipe = 0;
	if (shell->fd_base > 0)
		close(shell->fd_base);
	i = 0;
	int ret;
	while (i < j)
	{
		if (waitpid(-1, &ret, 0) == last_pid)
		{
			if (WIFEXITED(ret))
				g_global.error_dollars = WEXITSTATUS(ret);
		}
		i++;
	}
	// printf("g_global.error_dollars = %d\n", g_global.error_dollars);
}

void	printenv(char **tab)
{
	int i = 0;

	while (tab[i])
	{
		// dprintf(2, "[%s]\n", tab[i]);
		i++;
	}
	return ;
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
			break ;
		}
		i++;
	}
	i = 0;
	while ((shell->parse_env && shell->parse_env[i]) && (ft_strchr(shell->opt2[0], '/')))
	{
		shell->join = ft_strjoin_three(shell->parse_env[i], "/", shell->opt2[0]);
		if (access(shell->join, F_OK) == 0)
		{
			break ;
		}
		i++;
		free(shell->join);
		shell->join = NULL;
	}
	if (!shell->join)
		shell->join = ft_strdup(shell->opt2[0]);
	if (shell->parse_env)
	{
		free(shell->parse_env);
		shell->parse_env = NULL;
	}
	return (0);
}

int	test_execve(t_shell *shell)
{
	shell->new_env_tab = new_env_tab(shell);
	if (!shell->new_env_tab)
		return (0);
	ft_check_access_mini(0, shell, shell->new_env_tab);
	return (0);
}