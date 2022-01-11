/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2022/01/11 13:02:51 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_global;

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		// if (!g_global.no_ctrlc)
		// {
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		// }
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
	(void)shell;
	(void)env;
	(void)utils;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals);
}

// static	void	clear(t_shell *shell)
// {

// }

int	main(int ac, char **av, char **env)
{
	t_utils		utils;
	t_shell		shell;
	static char	*buffer;

	buffer = (char *) NULL;
	(void)ac;
	(void)av;
	mem(&utils, &shell);
	stock_env(env, &shell);
	setup(env, &utils, &shell);
	rl_outstream = stderr;
	while (1)
	{
		shell.fd_base = 0;
		buffer = prompt(&shell, buffer);
		if (buffer)
			add_history(buffer);
		// dprintf(2, "buffer = %s\n", buffer);
		if (make_token_lst(buffer, &shell))
		{
			// dprintf(2, "ALLOO\n");
			print_token_list(shell.token);
			parsing_dollars(&shell);
			if (parsing_errors_token(&shell))
				fill_cmd(&shell);
			if (shell.action)
				test_execve(&shell);
		}
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
		// clear(&shell);
	}
	return (0);
}
