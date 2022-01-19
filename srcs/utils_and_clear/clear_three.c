/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:10:52 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/18 18:46:13 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	dest = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!(dest))
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	int				i;
	int				j;
	char			*str;

	i = 0;
	j = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1));
	if (!(str))
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	j = 0;
	while (s3[j])
		str[i++] = s3[j++];
	str[i] = '\0';
	return (str);
}

char	*is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (&str[i]);
		i++;
	}
	return (str);
}

void	free_split(char **tab)
{
	int				i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_close_fd(t_shell *shell)
{
	close(shell->fd_in);
	close(shell->fd_out);
	close(shell->fd_temp);
	close(shell->pfd[0]);
	close(shell->pfd[1]);
	close(shell->fd_base);
}
