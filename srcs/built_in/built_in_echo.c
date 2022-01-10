/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:20 by tnave             #+#    #+#             */
/*   Updated: 2022/01/10 13:12:04 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_echo(char **opt, t_shell *shell)
{
	int	i;

	i = 0;
	(void)shell;
	while (opt[i])
	{
		if (write(1, opt[i], ft_strlen(opt[i])) == -1)
		{
			dprintf(2, "test echo :%s\n", strerror(errno));
			dprintf(2, "pid :%d \n", getpid());
			exit(1);
		}
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int	built_in_echo_n(char **opt, t_shell *shell)
{
	int	i;

	i = 0;
	(void)shell;
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
