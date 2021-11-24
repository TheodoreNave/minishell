/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:02:59 by tnave             #+#    #+#             */
/*   Updated: 2021/11/24 12:05:21 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFFER_SIZE 2048

# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char const *str);
char	*ft_strjoin(char *s1, char *s2);
int		get_len(char *str);
char	*ft_strdup(char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*get_str_new_line(char *new_line);
int		get_next_line(int fd, char **line);
char	*ft_strjoin_free(char *s1, char *s2);

#endif