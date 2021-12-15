/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/12/15 15:40:00 by tnave            ###   ########.fr       */
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

// void	opt_exec_mini(char **environ, t_utils *utils, t_utils_list *tmp)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		ft_error(0, strerror(errno), utils);
// 	if (pid == 0)
// 	{
// 		if (!tmp->prev)
// 			dup2(utils->fd_one, STDIN);
// 		else
// 			dup2(tmp->prev->pfd[STDIN], STDIN);
// 		if (tmp->next)
// 			dup2(tmp->pfd[STDOUT], STDOUT);
// 		else
// 			dup2(utils->fd_two, STDOUT);
// 		execve(tmp->path, tmp->cmd_opt, environ);
// 		exit(127);
// 	}
// 	else
// 		child(pid, utils, tmp);
// }

// void		suite_pipex(t_utils *utils, char **environ)
// {
// 	t_utils_list *tmp;

// 	tmp = utils->lst;
// 	while (tmp)
// 	{
// 		if (tmp->next)
// 		{
// 			if (pipe(tmp->pfd) == -1)
// 				ft_error(0, strerror(errno), utils);
// 		}
// 		opt_exec_mini(environ, utils, tmp);
// 		tmp = tmp->next;
// 	}
// }

// void		ft_check_access_mini(int i, t_shell *shell, t_utils *utils)
// {
// 	while (shell->environ && shell->environ[i])
// 	{
// 		utils->join = ft_strjoin_three(utils->parse_env[i],
// 			"/", shell->action->opt[0]);
// 			printf("========\n");
// 		printf("[%s]\n", utils->join);
// 			printf("========\n");
// 		if (access(utils->join, F_OK) == 0)
// 		{
// 			printf("cool\n");
// 			ft_lstadd_back(&utils->lst, ft_lstnew(shell->action->opt,
// 				ft_strdup(utils->join)));
// 		}
// 		else
// 		{
// 			printf("PAS BON LA COMMANDE\n");
// 			// break;
// 		}
// 		i++;
// 	}
// 	suite_pipex(utils, environ);
// }

int main(int ac, char **av, char **env)
{
    t_utils utils;
	t_shell shell;
	static char	*buffer = (char *)NULL;
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

		buffer = prompt(&shell, buffer);
		if (buffer)
			add_history(buffer);
		if (!parsing_shit(buffer, &shell))
			return (0);
		parsing_dollars(&shell);
		// print_list_z(shell.token);
		if (parsing_shit_two(&shell))
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

		print_new_lst(shell.action);
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
	}
	return (0);
}


// < fichier == O_RDONLY

// < == O_RDONLY
// ls < fichier
// cat < fichier
// [cat] [fichier]
// [ls] [fichier]