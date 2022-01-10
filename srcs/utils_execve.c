/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:36:35 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/10 18:17:55 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define BUFFER_SIZE 32

void	init_value(t_shell *shell, t_cmd_list *tmp)
{
	shell->opt2 = new_opt_action(tmp);
		if (!shell->opt2)
	return ;
	parse_les_redirections(tmp, shell);
	parse_env_2(shell);
}

void	reset_value(t_shell *shell)
{
	free(shell->join);
	shell->join = NULL;
	free_split(shell->opt2);
	shell->opt2 = NULL;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->fd_temp = -1;
	return ;
}

char	**new_opt_action(t_cmd_list *action)
{
	int i;
	int j;
	t_cmd_list *tmp;
	char **temp;

	i = 0;
	j = 0;
	tmp = action;
	temp = NULL;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->opt)
			i += ft_count_line(tmp->opt);
		if (tmp->fichier != NULL)
			i += 1;
		tmp = tmp->next;
	}
	tmp = action;
	temp = malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->opt)
		{
			while (tmp->opt[j])
			{
				temp[i] = ft_strdup(tmp->opt[j]);
				j++;
				i++;
			}
		}
		tmp = tmp->next;
		j = 0;
	}
	temp[i] = NULL;
	return (temp);
}

static char				*ft_strjoin_free(char *s1, char *s2)
{
	int				i;
	int				j;
	char			*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	free(s1);
	str[i] = '\0';
	return (str);
}

static char				*get_str_new_line(char *new_line)
{
	int				i;
	int				j;
	char			*str;

	i = 0;
	j = 0;
	if (ft_strchr(new_line, '\n'))
	{
		while (new_line[i] && new_line[i] != '\n')
			i++;
		str = ft_strdup(new_line + i + 1);
		while (new_line[j])
		{
			new_line[j] = str[j];
			j++;
		}
		new_line[j] = '\0';
		free(str);
		return (new_line);
	}
	return (NULL);
}

static int				get_len(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	int			i;
	char		*str;
	size_t		max;

	i = 0;
	str = (char*)s;
	max = ft_strlen(s);
	if (!s)
		return (NULL);
	if (!(str = malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (start > len)
		return (NULL);
	while (s[start] && len && start < max)
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return ((char*)str);
}

static char					*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*new_line;
	int				len;
	int				rd;
	static char 	*line;

	if (BUFFER_SIZE < 1 || fd < 0 || (read(fd, buff, 0) < 0))
		return (NULL);
	rd = 0;
	if (new_line == NULL)
		new_line = ft_strdup("");
	while (!ft_strchr(new_line, '\n') && (rd = read(fd, buff, BUFFER_SIZE)))
	{
		buff[rd] = '\0';
		new_line = ft_strjoin_free(new_line, buff);
	}
	len = get_len(new_line);
	line = ft_substr(new_line, 0, len);
	if (get_str_new_line(new_line) == NULL)
	{
		free(new_line);
		new_line = NULL;
		return (NULL);
	}
	return (line);
}




static void 	ft_heredoc(t_shell *shell, t_cmd_list *tmp)
{
		// int i;

		// i = 0;
		// (void)tmp;
		shell->fichier_temp = tmp->fichier;
		shell->fd_temp = open(tmp->fichier, O_RDWR | O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
		static char	*buffer_doc = (char *)NULL;
		while (1)
		{
			// shell->prompt_heredoc = 1;
			buffer_doc = readline("> ");
			if (!ft_strncmp(tmp->fichier, buffer_doc, ft_strlen(tmp->fichier)))
			{
				// shell->prompt_heredoc = 0;
				// rl_on_new_line();
				// rl_replace_line("", 0);
				g_global.read_here_doc = 1;
				break ;
			}
			write(shell->fd_temp, buffer_doc, ft_strlen(buffer_doc));
			write(shell->fd_temp, "\n", 1);
			// rl_on_new_line();
			// rl_replace_line("", 0);
		}
		printf("after break\n");
		if (!ft_strncmp(shell->opt2[0], "cat", 4))
		{
			// dprintf("%d\n", shell->fd_temp);
			printf("%s\n", get_next_line(shell->fd_temp));
			printf("coucou\n");
			g_global.read_here_doc = 1;
		}
		if (g_global.read_here_doc)
		{
			// write(shell->fd_temp, )
			// close(shell->fd_temp);
			// write(shell->fd_temp, NULL, 1);
			shell->fd_temp = 0;
			free(buffer_doc);
		}
		if (g_global.read_here_doc == 1)
			shell->fd_temp = open(tmp->fichier, O_TRUNC);
		// return (shell->fd_temp);
}

void 	parse_les_redirections(t_cmd_list *temp, t_shell *shell)
{
	t_cmd_list *tmp;

	tmp = temp;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->type_start == TYPE_REDIR_LEFT)
		{
			shell->fd_in = open(tmp->fichier, O_RDONLY);
			if (shell->fd_in < 0)
			{
				printf("bash: %s: No such file or directory\n", tmp->fichier);
				g_global.error_dollars = 1;
				shell->pipe = -1;
			}
			shell->fd_out = -1;
		}
		else if (tmp->type_start == TYPE_REDIR_RIGHT)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
			shell->fd_in = -1;
		}
		else if (tmp->type_start == TYPE_REDIR)
		{
			shell->fd_out = open(tmp->fichier, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
			shell->fd_in = -1;
		}
		else if (tmp->type_start == TYPE_HEREDOC && tmp->fichier != NULL)	// ADD cat exception
		{
			ft_heredoc(shell, tmp);
			// if (ft_strncmp(shell->opt2, "cat", 3)
			// ft_heredoc_cat()
			shell->fd_out = shell->fd_temp;
			shell->fd_in = -1;
		}
		tmp = tmp->next;
	}
}

