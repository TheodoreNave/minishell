/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_dollars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:25:28 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/16 13:34:11 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r');
}

int	ft_strlen_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strndup(char *str, int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (!(dest))
		return (NULL);
	while (str[i] && i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_dollars(t_shell *shell, char *word)
{
	(void)shell;
	int i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
