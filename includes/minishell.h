/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:56:31 by tnave             #+#    #+#             */
/*   Updated: 2021/08/03 15:58:23 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

#define BUFFER_SIZE 2048

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
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*get_str_new_line(char *new_line);
int		get_next_line(int fd, char **line);
char	*ft_strjoin_free(char *s1, char *s2);

#endif