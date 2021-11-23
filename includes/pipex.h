/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:42:34 by tnave             #+#    #+#             */
/*   Updated: 2021/10/15 15:40:42 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <memory.h>

# define STDIN 0
# define STDOUT 1

typedef struct s_utils_list
{
	char				*cmd;
	char				**cmd_opt;
	char				*path;
	int					pfd[2];

	struct s_utils_list	*prev;
	struct s_utils_list	*next;

}	t_utils_list;

typedef struct s_utils
{
	int					fd_one;
	int					fd_two;
	int					invalid_fd;
	char				**parse_env;
	int					cmd_ok;
	char				*join;
	char				**temp;
	int					p;
	int					wrong_cmd;
	char				*error_msg;
	t_utils_list		*lst;

}	t_utils;

int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				parse_env(char **env, t_utils *utils);

char			**ft_split(char const *s, char c);

void			*ft_memset(void *b, int c, size_t len);

char			*is_slash(char *str);

void			free_split(char **tab);

char			*ft_strdup(char *s1);

char			*ft_strjoin_three(char *s1, char *s2, char *s3);

char			*ft_strjoin(char *s1, char *s2);

size_t			ft_strlen(const char *str);

void			ft_check_access(int ac, char **av, t_utils *utils);

void			parse_cmd(int argc, char **argv, t_utils *utils);

t_utils_list	*ft_lstnew(char **cmd_opt, char *path);

void			ft_lstadd_back(t_utils_list **alst, t_utils_list *new);

int				ft_count_line(char **str);

void			print_list(t_utils_list *tmp);

void			ft_lstclear(t_utils_list **lst, void (*del)(void *));

void			ft_error(int i, char *str, t_utils *utils);
void			add_opt(t_utils *utils);

void			opt_exec(char **av, char **environ,
					t_utils *utils, t_utils_list *tmp);

void			pipe_in(int pfd[2], t_utils *utils,
					 char **argv, char **environ);

void			pipe_out(int pfd[2], t_utils *utils,
					 char **argv, char **environ);

void			exit_function(t_utils *utils);

void			ft_check_access_two(char **av, int i, int j, t_utils *utils);

void			assign_error(t_utils *utils);

void			ft_free(char **ptr);

void			show_error(char *str);

void			error_msg(t_utils *utils);

void			utils_cmd_ok(char **av, int j, t_utils *utils);

void			child(pid_t pid, t_utils *utils, t_utils_list *tmp);

#endif