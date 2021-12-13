/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:20 by tnave             #+#    #+#             */
/*   Updated: 2021/12/13 11:32:39 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// MULTI ARGUMENT ECHOE

int		built_in_echo(char **opt)
{
	int i = 0;
	if (!opt)
		return (0);
	while (opt[i])
	{
		write(1, opt[i], ft_strlen(opt[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int		built_in_echo_n(char **opt)
{
	int i;

	i = 0;
	if (!opt)
		return (0);
	while (opt[i])
	{
		write(1, opt[i], ft_strlen(opt[i]));
		write(1, " ", 1);
		i++;
	}
	return (0);
}