/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:56:31 by tnave             #+#    #+#             */
/*   Updated: 2021/12/03 14:11:01 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "pipex.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <err.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFF_MAX 2048
# define TYPE_WORD 1
# define TYPE_SIMPLE_QUOTE 2
# define TYPE_DOUBLE_QUOTE 3
# define TYPE_PIPE 4
# define TYPE_REDIR 5
# define TYPE_REDIR_LEFT 6
# define TYPE_REDIR_RIGHT 7
# define TYPE_ENV 8
# define TYPE_DOLLARS 9
# define TYPE_HEREDOC 10
# define TYPE_END 11


typedef	struct s_token_list			// TOKEN PARSING
{
	int		type;
	char	*word;

	struct s_token_list *next;
	struct s_token_list *prev;

} t_token_list;

typedef struct s_cmd_list			// MAIN CMD LIST PARSE
{
	//char 	*cmd;
	int 	type_start;		// <
	char	*fichier;
	char 	**opt;
	int 	type_end;

	struct s_cmd_list *next;
	struct s_cmd_list *prev;
}	t_cmd_list;

typedef struct s_shell				// MAIN STRUCTURE
{
	char 			buff_temp[BUFF_MAX];
	int				x;
	int				i;
	int				quote;
	t_token_list	*token;
	t_cmd_list		*action;

}	t_shell;

void 	print_new_lst(t_cmd_list *lst);

void	malloc_opt(t_token_list **tmp, t_cmd_list *tpmp);

int	init_lst_redir(t_shell *shell, t_token_list **tmp, t_cmd_list *tpmp);


int		fill_cmd(t_shell *shell);

void 	parse_dollars(char *str, t_shell *shell);

int		ft_error_two(char *str, t_shell *shell, int error);

int		add_to_buff_quote(char *prompt, char c, t_shell *shell);

void	ft_lstclear_action(t_cmd_list **action);

void	ft_lstadd_back_action(t_cmd_list **action, t_cmd_list *new);

void 	print_list_z(t_token_list * token);

void	clear_buff(t_shell *shell);

int 	parsing_shit_two(t_shell *shell);

t_token_list	*ft_lstnew_shell(int type, char *word);

void	ft_lstclear_shell(t_token_list **token);

void	ft_lstadd_back_shell(t_token_list **token, t_token_list *new);

int		ft_lstsize_shell(t_token_list *lst);

void	add_to_buff_no_space(t_shell *shell, char c);

void	add_to_buff(t_shell *shell, char c);

int		parsing_shit(char *buff, t_shell *shell);

void	mem(t_utils *utils, t_shell *shell);

void	signals(int sig);

int		parse_env_minishell(char **env, t_utils *utils);

void	ft_check_access_minishell(char *buff, t_utils *utils);

void	ft_check_access_two_minishell(char *buff, int i, int j, t_utils *utils);

void	utils_cmd_ok_minishell(char *buff, int j, t_utils *utils);

void	opt_exec_minishell(char **environ, t_utils *utils, t_utils_list *tmp);

void	child_mini(pid_t pid, t_utils *utils, t_utils_list *tmp);

#endif