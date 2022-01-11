/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:56:31 by tnave             #+#    #+#             */
/*   Updated: 2022/01/12 00:15:33 by tigerber         ###   ########.fr       */
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
# include <limits.h>
# include <err.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFF_MAX 2048
# define TYPE_WORD 1
# define TYPE_SIMPLE_QUOTE 2
# define TYPE_PIPE 4
# define TYPE_REDIR 5
# define TYPE_REDIR_LEFT 6
# define TYPE_REDIR_RIGHT 7
# define TYPE_ENV 8
# define TYPE_DOLLARS 9
# define TYPE_HEREDOC 10
# define TYPE_END 11

# define STDIN 0
# define STDOUT 1

typedef struct s_dol
{
	char			*word_dol;

	struct s_dol	*next;
	struct s_dol	*prev;
}					t_dol;

typedef struct s_global
{
	int			error_dollars;
	int			minus;
	int 		no_ctrlc;
	int			read_here_doc;
}				t_global;

typedef struct s_env
{
	char			*var_env;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_token_list
{
	int					type;
	char				*word;

	struct s_token_list	*next;
	struct s_token_list	*prev;

}						t_token_list;

typedef struct s_cmd_list
{
	int					type_start;
	char				*fichier;
	char				**opt;
	int					type_end;
	int					fd_in;
	int					fd_out;

	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}	t_cmd_list;

typedef struct s_shell
{
	char			buff_temp[BUFF_MAX];
	char			buff_pwd[BUFF_MAX];
	int				x;
	int				i;
	int				quote;
	t_token_list	*token;
	t_cmd_list		*action;
	t_dol			*dol;
	int				on;
	char			*pwd_temp;
	t_env			*environ;
	int				simple_quote;
	char			*dollar_var;
	int				is_dol;
	int				error_dol;
	t_utils			*utils;
	char			**parse_env;
	char			*join;
	char			**opt2;
	char			**new_env_tab;
	int				fd_base;
	int				fd_in;
	int				fd_out;
	int				fd_temp;
	char			*fichier_temp;
	int				prompt_heredoc;
	int				pfd[2];
	int				pipe;
	int				prompt;
	char			*tmp_file;
}					t_shell;

void			builtin_echo(char **opt, t_shell *shell);

void			signals2(int sig);

void			ft_strcpy(char *buff, char *str);

void			ft_putstr_fderr(char *str, char *str2);

void			init_value(t_shell *shell, t_cmd_list *tmp);

void			reset_value(t_shell *shell);

int				built_in_check_2(char **built_in, t_shell *shell);

int				ft_strchr(char *str, char c);

void			testfork(char **environ, t_shell *shell, t_cmd_list *tmp);

pid_t			opt_exec_mini_without_pipe(char **environ, t_shell *shell,
					t_cmd_list *tmp);

pid_t			opt_exec_mini(char **environ, t_shell *shell, t_cmd_list *tmp);

void			child_mini(pid_t pid, t_shell *shell, t_cmd_list *tmp);

char			**new_env_tab(t_shell *shell);

char			**new_opt_action(t_cmd_list *action);

void			print_new_opt(char **tab);

int				is_type_redir(int type);

int				go_to_home(t_shell *shell);

int				check_dollars(char *word);

int				is_whitespace(int c);

int				ft_strlen_space(char *str);

char			*ft_strndup(char *str, int size);

void			child_minishell(pid_t pid, t_cmd_list *tmp);

void			pipe_or_not(t_shell *shell, char **tab,
					char **opt, t_cmd_list *tmp);

void			parse_les_redirections(t_cmd_list *temp, t_shell *shell);

int				parse_env_2(t_shell *shell);

int				test_execve(t_shell *shell);

void			ft_check_access_mini(int i, t_shell *shell, char **env);

int				ft_isalnum(int c);

char			*ft_strrev(char *str);

int				ft_count_nbr(long int nb);

char			*ft_itoa(int n);

char			*dollars_question(char *word);

int				ft_strcmp(char *s1, char *s2);

int				check_name_variable(char *str, t_shell *shell, int j);

int				built_in_unset(t_shell *shell, char **opt);

void			ft_lstclear_env(t_env **env);

int				built_in_echo_n(char **opt, t_shell *shell);

char			*join_dollars(t_shell *shell);

void			new_token_dollars(char *word, t_shell *shell);

t_dol			*ft_lstnew_dol(char *word);

void			ft_lstadd_back_dol(t_dol **dol, t_dol *new);

void			ft_lstclear_dol(t_dol **dol);

void			print_list_dol(t_dol *token);

int				ft_strlen_space(char *str);

char			*convert_dollars(char *word, t_shell *shell);

int				parsing_dollars(t_shell *shell);

int				ft_putstr_quotes(char *str);

int				ft_strncmpp(const char *s1, const char *s2, size_t n);

int				ft_strlen_char(char *str, char c);

int				count_env_lst(t_env *env);

int				print_sort_env(t_env *env);

void			add_symbol(t_shell *shell, char symbole);

int				is_symbol(char c);

void			empty_buff_in_lst(t_shell *shell, char symbole);

int				built_in_exit(t_shell *shell, char **opt);

int				built_in_echo(char **opt, t_shell *shell);

int				boucle_unset(t_shell *shell, char *opt);

int				built_in_export(char **opt, t_env *environ, t_shell *shell);

int				parse_pwd_two(t_shell *shell);

int				parse_pwd(t_shell *shell);

void			print_env_lst(t_env *env, int indic);

t_env			*ft_lstnew_env(char *variable);

void			ft_lstadd_back_env(t_env **environ, t_env *new);

int				stock_env(char **env, t_shell *shell);

char			*prompt(t_shell *shell, char *buff);

int				built_in_env(char **env);

int				is_built_in(char *cmd);

int				built_in_pwd(t_shell *shell);

int				built_in_cd(t_shell *shell, char **opt);

int				built_in_check(char **built_in, t_shell *shell);

void			print_new_lst(t_cmd_list *lst);

void			malloc_opt(t_token_list **tmp, t_cmd_list *tpmp);

int				init_lst_redir(t_shell *shell, t_token_list **tmp,
					t_cmd_list *tpmp);

int				fill_cmd(t_shell *shell);

void			parse_dollars(char *str, t_shell *shell);

int				ft_error_two(char *str, t_shell *shell, int error);

int				add_to_buff_quote(char *prompt, char c, t_shell *shell);

void			ft_lstclear_action(t_cmd_list **action);

void			ft_lstadd_back_action(t_cmd_list **action, t_cmd_list *new);

void			print_token_list(t_token_list *token);

void			clear_buff(t_shell *shell);

int				parsing_errors_token(t_shell *shell);

t_token_list	*ft_lstnew_shell(int type, char *word);

void			ft_lstclear_shell(t_token_list **token);

void			ft_lstadd_back_shell(t_token_list **token, t_token_list *new);

int				ft_lstsize_shell(t_token_list *lst);

void			add_to_buff_no_space(t_shell *shell, char c);

void			add_to_buff(t_shell *shell, char c);

int				make_token_lst(char *buff, t_shell *shell);

void			mem(t_utils *utils, t_shell *shell);

void			signals(int sig);

int				parse_env_minishell(char **env, t_utils *utils);

void			ft_check_access_minishell(char *buff, t_utils *utils);

void			ft_check_access_two_minishell(char *buff, int i, int j,
					t_utils *utils);

void			utils_cmd_ok_minishell(char *buff, int j, t_utils *utils);

void			opt_exec_minishell(char **environ, t_utils *utils,
					t_utils_list *tmp);

extern t_global	g_global;

#endif
