/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:30:29 by tnave             #+#    #+#             */
/*   Updated: 2021/12/21 14:44:10 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	ft_check_access_minishell(char *buff, t_utils *utils)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (j < 1)
// 	{
// 		// printf("test access\n");
// 		ft_check_access_two_minishell(buff, i, j, utils);
// 		utils->cmd_ok = 0;
// 		utils->wrong_cmd = 0;
// 		j++;
// 	}
// }

// void	ft_check_access_two_minishell(char *buff, int i, int j, t_utils *utils)
// {
// 	while (utils->parse_env && utils->parse_env[i] && !utils->cmd_ok)
// 	{
// 		printf("split\n");
// 		utils->temp = ft_split(&buff[j], ' ');
// 		utils->join = ft_strjoin_three(utils->parse_env[i], "/", utils->temp[0]);
// 		// printf("utilsjoin = %s\n", utils->join);
// 		if (access(utils->join, F_OK) == 0)
// 		{
// 			ft_lstadd_back(&utils->lst, ft_lstnew(utils->temp,
// 					ft_strdup(utils->join)));
// 			printf("utils->temp[] = %s\n", utils->temp[0]);
// 			printf("utils->temp[] = %s\n", utils->temp[1]);
// 			utils->cmd_ok = 1;
// 			// printf("cmd ok\n");
// 		}
// 		else
// 		{
// 			if (utils->wrong_cmd == 0)
// 			{
// 				utils->error_msg = ft_strdup(utils->temp[0]);
// 				utils->wrong_cmd = 1;
// 			}
// 			free_split(utils->temp);
// 			utils->temp = NULL;
// 		}
// 		free(utils->join);
// 		i++;
// 	}
// 	utils_cmd_ok_minishell(buff, j, utils);
// }

// void	utils_cmd_ok_minishell(char *buff, int j, t_utils *utils)
// {
// 	if (!utils->cmd_ok)
// 	{
// 		utils->temp = ft_split(&buff[j], ' ');
// 		ft_lstadd_back(&utils->lst, ft_lstnew(utils->temp, NULL));
// 		if (!utils->invalid_fd)
// 		{
// 			write(2, "bash: ", 6);
// 			write(2, utils->error_msg, ft_strlen(utils->error_msg));
// 			write(2, ": Command not found\n", 20);
// 			free(utils->error_msg);
// 		}
// 		else
// 			error_msg(utils);
// 	}
// 	else
// 		error_msg(utils);
// }

// void	opt_exec_minishell(char **environ, t_utils *utils, t_utils_list *tmp)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		ft_error(0, strerror(errno), utils);
// 	if (pid == 0)
// 	{
// 		// if (!tmp->prev)
// 		// 	dup2(utils->fd_one, STDIN);
// 		// else
// 		// 	dup2(tmp->prev->pfd[STDIN], STDIN);
// 		// if (tmp->next)
// 		// 	dup2(tmp->pfd[STDOUT], STDOUT);
// 		// else
// 		// 	dup2(utils->fd_two, STDOUT);
// 		// if (ft_strncmp(av[1], "/dev/urandom", 16) == 0)
// 		// 	close(tmp->prev->pfd[STDIN]);
// 		execve(tmp->path, tmp->cmd_opt, environ);
// 		exit(127);
// 	}
// 	else
// 		child_mini(pid, utils, tmp);
// }

// void	child_mini(pid_t pid, t_utils *utils, t_utils_list *tmp)
// {
// 	(void)utils;
// 	(void)tmp;
// 	waitpid(pid, NULL, 0);
// 	// if (tmp->prev)
// 	// 	close(tmp->prev->pfd[STDIN]);
// 	// if (tmp->next)
// 	// 	close(tmp->pfd[STDOUT]);
// 	// if (!tmp->next)
// 	// 	printf("coucou\n");
// 		// exit_function(utils);
// }
	// signal(SIGQUIT, function_ctrl-\); nothing
	// signal(???, function_ctrl-d); exit the shell