/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:56:31 by tnave             #+#    #+#             */
/*   Updated: 2021/11/23 16:08:48 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

#define BUFFER_SIZE 2048

# include "pipex.h"
// # include "get_next_line.h"
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

size_t	ft_strlen(char const *str);
char	*ft_strjoin(char *s1, char *s2);
int		get_len(char *str);
char	*ft_strdup(char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*get_str_new_line(char *new_line);
int		get_next_line(int fd, char **line);
char	*ft_strjoin_free(char *s1, char *s2);
int	parse_env_minishell(char **env, t_utils *utils);

void	ft_check_access_minishell(char *buff, t_utils *utils);

void	ft_check_access_two_minishell(char *buff, int i, int j, t_utils *utils);

void	utils_cmd_ok_minishell(char *buff, int j, t_utils *utils);

void	opt_exec_minishell(char **environ, t_utils *utils, t_utils_list *tmp);



#endif