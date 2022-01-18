/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:38:32 by tnave             #+#    #+#             */
/*   Updated: 2022/01/18 14:07:32 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_word_count(char const *str, char c)
{
	int		i;
	int		count;
	int		cmpt;

	i = 0;
	count = 0;
	cmpt = 0;
	while (str[i])
	{
		if (cmpt == 1 && str[i] == c)
			cmpt = 0;
		if (cmpt == 0 && str[i] != c)
		{
			cmpt = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	*new_full_string(char const *str, int l, int word)
{
	char	*new;
	int		size;
	int		j;

	size = l - word;
	j = 0;
	new = (char *)malloc(sizeof(char) * (word + 1));
	if (!(new))
		return (NULL);
	while (size < l)
	{
		new[j] = str[size];
		size++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	**schwifty(char **str, char const *s, char c, int words)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	while (++i < words)
	{
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
		{
			j++;
			k++;
		}
		str[i] = new_full_string(s, j, k);
		k = 0;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**str;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(str))
		return (NULL);
	str = schwifty(str, s, c, words);
	return (str);
}
