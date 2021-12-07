/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/12/07 17:51:57 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	char *temp;
	char *join_temp;
	char buff_pwd[1024];

	if (sig == SIGINT)
	{
		temp = getcwd(buff_pwd, sizeof(buff_pwd));
		if (!temp)
			free(temp);
		join_temp = ft_strjoin(temp , " $> ");
		// rl_on_new_line();
		// if (rl_on_new_line())
		write(1, "\n", 1);
		// rl_redisplay();
		rl_replace_line("", 0);
		write(1, join_temp, strlen(join_temp));
		// printf("\n%s", join_temp);
		free(join_temp);
	}
}

void	mem(t_utils *utils, t_shell *shell)
{
	ft_memset(utils, 0, sizeof(t_utils));
	ft_memset(shell, 0, sizeof(t_shell));
}


char	*prompt(t_shell *shell, char *buff)
{
	char *temp;
	char *join_temp;

	temp = getcwd(shell->buff_pwd, sizeof(shell->buff_pwd));
	if (!temp)
		free(temp);
	join_temp = ft_strjoin(temp , " $> ");
	buff = readline(join_temp);
	if (!buff)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	// free(join_temp);
	return (buff);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    // char *rl_line_buffer;
    t_utils utils;
	t_shell shell;

	mem(&utils, &shell);
	if (chdir(getenv("HOME")) == -1)
		ft_error_two("chdir()", &shell, 1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals);
    while (1)
    {
		rl_line_buffer = prompt(&shell, rl_line_buffer);
		add_history(rl_line_buffer);
		if (!parsing_shit(rl_line_buffer, &shell))
			return (0);
		if (parsing_shit_two(&shell))
			fill_cmd(&shell);

		parse_env_minishell(env, &utils);

		if (is_built_in(shell.action->opt[0]))
		{
			printf("cmd is ok\n");
			built_in_check(env, shell.action->opt, &shell);
		}
		else
		{
				printf("pas la bonne commande\n");
		}
		// free(buff);
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
		// print_new_lst(shell.action);
		// print_list_z(shell.token);
	}
    write(1, "ciao\n", 5);
	return (0);
}
