/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:17:05 by tnave             #+#    #+#             */
/*   Updated: 2021/12/14 12:31:16 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strrev(char *str)
{
	int			i;
	int			len;
	char		temp;

	i = 0;
	len = ft_strlen(str) - 1;
	if (str[0] == '-')
		i++;
	while (i < len)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
		i++;
		len--;
	}
	return (str);
}

int	ft_count_nbr(long int nb)
{
	long int	i;

	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	long int	i;
	long int	nb;
	char		*str;
	long int	count;

	i = -1;
	nb = n;
	count = ft_count_nbr(nb);
	str = malloc(sizeof(char) * count + 1);
	if (!(str))
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
		i++;
	}
	while (++i < count)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
	}
	str[i] = '\0';
	ft_strrev(str);
	return (str);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
