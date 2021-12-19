/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/12/19 20:46:37 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
		buffer = prompt(&shell, buffer);
		if (buffer)
			add_history(buffer);
		if (!make_token_lst(buffer, &shell))
			return (0);
		parsing_dollars(&shell);
		if (parsing_errors_token(&shell))
			fill_cmd(&shell);
		if (shell.action)
		{
			test_execve(&shell);
			// if (!built_in_check(shell.action->opt, &shell))
			// {
			// 	printf("cmd is not built_in\n");
			// 	// stock dans une liste et balancer dans pipex si necessaire au dernier moment
			// }
		}
		// print_new_lst(shell.action);
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
		// print_token_list(shell.token);
		// print_env_lst(shell.environ);
	}
	return (0);
}
