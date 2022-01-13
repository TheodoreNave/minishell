/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2022/01/13 17:36:03 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PROB wc -c fichier non existant ensuite wc -c fichier valide 
#include "../includes/minishell.h"

t_global	g_global;

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		if (!g_global.no_ctrlc)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_global.error_dollars = 130;
	}
}

void	mem(t_utils *utils, t_shell *shell)
{
	ft_memset(utils, 0, sizeof(t_utils));
	ft_memset(shell, 0, sizeof(t_shell));
}

static void	setup(char **env, t_utils *utils, t_shell *shell)
{
	(void)utils;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals);
	stock_env(env, shell);
}

void	clear(t_shell *shell)
{
	ft_lstclear_shell(&shell->token);
	ft_lstclear_action(&shell->action);
	if (shell->new_env_tab)
	{
		free_split(shell->new_env_tab);
		shell->new_env_tab = NULL;
	}
	if (shell->opt2)
	{
		free_split(shell->opt2);
		shell->opt2 = NULL;	
	}
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
}

void	clear_end(t_shell *shell)
{
	clear(shell);
	ft_lstclear_env(&shell->environ);
	if (shell->home)
	{
		free(shell->home);
		shell->home = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_utils		utils;
	t_shell		shell;
	static char	*buffer;

	buffer = (char *) NULL;
	(void)av;
	if (ac != 1)
		return (0);
	mem(&utils, &shell);
	setup(env, &utils, &shell);
	rl_outstream = stderr;
	while (1)
	{
		shell.fd_base = 0;
		buffer = prompt(&shell, buffer);
		if (buffer)
			add_history(buffer);
		if (make_token_lst(buffer, &shell))
		{
			parsing_dollars(&shell);
			if (parsing_errors_token(&shell))
				fill_cmd(&shell);
			if (shell.action)
				test_execve(&shell);
		}
		clear(&shell);
	}
	clear_end(&shell);
	return (0);
}
