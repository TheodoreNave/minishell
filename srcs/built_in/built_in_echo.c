/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:20 by tnave             #+#    #+#             */
/*   Updated: 2021/12/09 01:56:50 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		built_in_echo(char **opt)
{
	if (!opt[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!strcmp(opt[1], "-n"))
	{
		if (!opt[2])
			return (0);
		else
			write(1, opt[2], ft_strlen(opt[2]));
	}
	if (strcmp(opt[1], "-n"))
	{
		write(1, opt[1], ft_strlen(opt[1]));
		write(1, "\n", 1);
	}
	return (0);
}