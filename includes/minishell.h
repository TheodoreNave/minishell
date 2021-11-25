/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:56:31 by tnave             #+#    #+#             */
/*   Updated: 2021/11/25 17:16:12 by tnave            ###   ########.fr       */
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
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <err.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFF_MAX 2048
# define TYPE_PIPE 1
# define TYPE_SIMPLE_QUOTE 2
# define TYPE_DOUBLE_QUOTE 3
# define TYPE_WORD 4
# define TYPE_REDIR 5
# define TYPE_ENV 6
# define TYPE_DOLLARS 7
# define TYPE_END 8


typedef	struct s_token_list			// TOKEN PARSING
{
	int		type;
	char	*word;

	struct s_token_list *next;
	struct s_token_list *prev;

} t_token_list;

typedef struct s_cmd_list			// MAIN CMD LIST PARSE
{
	char 	*cmd;
	int 	type;

	struct s_cmd_list *next;
	struct s_cmd_list *prev;
}	t_cmd_list;

typedef struct s_shell				// MAIN STRUCTURE
{
	char 			buff_temp[BUFF_MAX];
	int				x;
	t_token_list	*token;

}	t_shell;











// ls -la wc | wc -c




void	parsing_shit_two(t_shell *shell);

t_token_list	*ft_lstnew_shell(int type, char *word);

void	ft_lstclear_shell(t_token_list **token);

void	ft_lstadd_back_shell(t_token_list **token, t_token_list *new);

int		ft_lstsize_shell(t_token_list *lst);

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