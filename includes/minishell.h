/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:56:31 by tnave             #+#    #+#             */
/*   Updated: 2021/11/24 12:28:15 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "pipex.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef	struct s_shell
{

} t_shell;

int	parse_env_minishell(char **env, t_utils *utils);

void	ft_check_access_minishell(char *buff, t_utils *utils);

void	ft_check_access_two_minishell(char *buff, int i, int j, t_utils *utils);

void	utils_cmd_ok_minishell(char *buff, int j, t_utils *utils);

void	opt_exec_minishell(char **environ, t_utils *utils, t_utils_list *tmp);

void	child_mini(pid_t pid, t_utils *utils, t_utils_list *tmp);

#endif