/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2022/01/06 15:51:16 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct 	s_global
{
	int			error_dollars;

}				t_global;

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		// shell->error_dol = 1;
		// Error message 130 si script sinon simple retour ligne message 1
	}
}

void	mem(t_utils *utils, t_shell *shell)
{
	ft_memset(utils, 0, sizeof(t_utils));
	ft_memset(shell, 0, sizeof(t_shell));
}

int main(int ac, char **av, char **env)
{
    t_utils utils;
	t_shell shell;
	static char	*buffer = (char *)NULL;

	(void)ac;
	(void)av;
	mem(&utils, &shell);
	stock_env(env, &shell);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals);
    while (1)
    {
		shell.fd_base = 0;
		buffer = prompt(&shell, buffer);
		if (buffer)
			add_history(buffer);
		if (buffer && !make_token_lst(buffer, &shell))
			return (0);
		parsing_dollars(&shell);
		if (parsing_errors_token(&shell))
			fill_cmd(&shell);
		if (shell.action)
		{
			// print_new_lst(shell.action);
			test_execve(&shell);
		}
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
		// print_token_list(shell.token);
		// print_env_lst(shell.environ);
	}
	return (0);
}
