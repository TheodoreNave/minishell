/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/11/24 12:36:37 by tnave            ###   ########.fr       */
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

void	ft_check_access_minishell(char *buff, t_utils *utils)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 1)
	{
		printf("test access\n");
		ft_check_access_two_minishell(buff, i, j, utils);
		utils->cmd_ok = 0;
		utils->wrong_cmd = 0;
		j++;
	}
}

void	ft_check_access_two_minishell(char *buff, int i, int j, t_utils *utils)
{
	while (utils->parse_env && utils->parse_env[i] && !utils->cmd_ok)
	{
		utils->temp = ft_split(&buff[j], ' ');
		utils->join = ft_strjoin_three(utils->parse_env[i], "/", utils->temp[0]);
		if (access(utils->join, F_OK) == 0)
		{
			ft_lstadd_back(&utils->lst, ft_lstnew(utils->temp,
					ft_strdup(utils->join)));
			printf("utils->temp[] = %s\n", utils->temp[0]);
			printf("utils->temp[] = %s\n", utils->temp[1]);
			utils->cmd_ok = 1;
			printf("cmd ok\n");
		}
		else
		{
			if (utils->wrong_cmd == 0)
			{
				utils->error_msg = ft_strdup(utils->temp[0]);
				utils->wrong_cmd = 1;
			}
			free_split(utils->temp);
			utils->temp = NULL;
		}
		free(utils->join);
		i++;
	}
	utils_cmd_ok_minishell(buff, j, utils);
}

void	utils_cmd_ok_minishell(char *buff, int j, t_utils *utils)
{
	if (!utils->cmd_ok)
	{
		utils->temp = ft_split(&buff[j], ' ');
		ft_lstadd_back(&utils->lst, ft_lstnew(utils->temp, NULL));
		if (!utils->invalid_fd)
		{
			write(2, "bash: ", 6);
			write(2, utils->error_msg, ft_strlen(utils->error_msg));
			write(2, ": Command not found\n", 20);
			free(utils->error_msg);
		}
		else
			error_msg(utils);
	}
	else
		error_msg(utils);
}

void	opt_exec_minishell(char **environ, t_utils *utils, t_utils_list *tmp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(0, strerror(errno), utils);
	if (pid == 0)
	{
		if (!tmp->prev)
			dup2(utils->fd_one, STDIN);
		else
			dup2(tmp->prev->pfd[STDIN], STDIN);
		if (tmp->next)
			dup2(tmp->pfd[STDOUT], STDOUT);
		else
			dup2(utils->fd_two, STDOUT);
		// if (ft_strncmp(av[1], "/dev/urandom", 16) == 0)
		// 	close(tmp->prev->pfd[STDIN]);
		execve(tmp->path, tmp->cmd_opt, environ);
		exit(127);
	}
	else
		child_mini(pid, utils, tmp);
}

void	child_mini(pid_t pid, t_utils *utils, t_utils_list *tmp)
{
	(void)utils;
	(void)tmp;
	waitpid(pid, NULL, 0);
	if (tmp->prev)
		close(tmp->prev->pfd[STDIN]);
	if (tmp->next)
		close(tmp->pfd[STDOUT]);
	if (!tmp->next)
		printf("coucou\n");
		// exit_function(utils);
}


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    char *buff;
    t_utils utils;
    t_utils_list *tmp;
	int i = 0;

	// signal(SIGINT, function_ctrl-c); new prompt newline
	// signal(SIGQUIT, function_ctrl-\); nothing
	// signal(???, function_ctrl-d); exit the shell
    ft_memset(&utils, 0, sizeof(t_utils));
    parse_env_minishell(env, &utils);
	while (utils.parse_env[i])
	{
		printf("env = %s\n", utils.parse_env[i]);
		i++;
	}
	write(1, "$> ", 3);
    while (get_next_line(0, &buff))
    {
		printf("yo\n");
		// buff = ls -la
		// split pour metre ls et -la dans une liste
		// on envoi la liste
		ft_check_access_minishell(buff, &utils);
        // ft_check_access(ac_bis, av_bis, &utils);

        tmp = utils.lst;
		while (tmp)
		{
			if (tmp->next)
			{
				if (pipe(tmp->pfd) == -1)
					ft_error(0, strerror(errno), &utils);
			}
			opt_exec_minishell(env, &utils, tmp);
			tmp = tmp->next;
		}
        write(1, "$> ", 3);
	}
    write(1, "ciao\n", 5);
}