/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/11/25 19:12:52 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//before ac = 2 av[0] = ./pipex av[1] ls -la

int	parse_env_minishell(char **env, t_utils *utils)
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
	if (sig == SIGQUIT)
	{
		return ;
	}
	else if (sig == SIGINT)
	{
		sig = SIGCONT;
		write(1, "\n", 1);
		return ;
	}
	el
}

void	mem(t_utils *utils, t_shell *shell)
{
	ft_memset(utils, 0, sizeof(t_utils));
	ft_memset(shell, 0, sizeof(t_shell));
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    char *buff;
    t_utils utils;
	t_shell shell;
	// t_token_list *tmp;
	// int i = 0;

	mem(&utils, &shell);
    parse_env_minishell(env, &utils);
		signal(SIGQUIT, signals);
		signal(SIGINT, signals);
    while (1)
    {
		buff = readline("Minishell $> ");
		parsing_shit(buff, &shell);
		// parsing_shit_two(&shell);
		(void)buff;
		// printf("buff = %s\n", buff);
	}
    write(1, "ciao\n", 5);
}