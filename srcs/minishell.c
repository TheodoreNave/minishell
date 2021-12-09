/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/12/09 02:02:23 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_env_minishell(char **env, t_utils *utils) // ?????
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			utils->parse_env = ft_split(is_slash(env[i]), ':');
			return (1);
		}
		i++;
	}
	return (0);
}

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

	(void)ac;
	(void)av;
	mem(&utils, &shell);
	if (chdir(getenv("HOME")) == -1)
		ft_error_two("chdir()", &shell, 1);

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals);
	stock_env(env, &shell);
	// print_env_lst(shell.environ);
    while (1)
    {
		rl_line_buffer = prompt(&shell, rl_line_buffer);
		add_history(rl_line_buffer);
		if (!parsing_shit(rl_line_buffer, &shell))
			return (0);
		if (parsing_shit_two(&shell))
			fill_cmd(&shell);

		parse_env_minishell(env, &utils);

		if (shell.action)
		{
			if (!built_in_check(shell.action->opt, &shell))
			{
				printf("cmd is not built_in\n");
				// stock dans une liste et balancer dans pipex si necessaire au dernier moment
			}
		}
		// free(rl_line_buffer); //free dans une fonction pour la norme
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
		// print_new_lst(shell.action);
		// print_list_z(shell.token);
	}
    write(1, "ciao\n", 5);
	return (0);
}
