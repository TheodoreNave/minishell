/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:47 by tnave             #+#    #+#             */
/*   Updated: 2022/01/12 18:42:18 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long	ft_atoi(const char *nptr)
{
	long	i;
	long	res;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' '))
	{
		i++;
	}
	if (nptr[i] == '-')
	{
		neg = -1;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10;
		res = res + (nptr[i] - 48);
		i++;
	}
	return (res * neg);
}

int	ft_check_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		g_global.minus = 1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	built_in_exit(t_shell *shell, char **opt)
{
	long	error;

	error = 0;
	if (shell->environ)
		ft_lstclear_env(&shell->environ);
	if (shell->action)
		ft_lstclear_action(&shell->action);
	if (shell->dol)
		ft_lstclear_dol(&shell->dol);
	if (opt[2])
	{
		dprintf(2, "exit = %s\n", opt[2]);
		write(2, "exit\n", 6);
		ft_putstr_fderr("bash: exit: too many arguments\n", NULL);
		clear(shell);
		exit(1);
	}
	if (opt[1])
	{
		if (ft_check_is_digit(opt[1]) || (ft_strlen(opt[1]) > 18 && !g_global.minus))
		{
			write(2, "exit\n", 6);
			ft_putstr_fderr("bash: exit: %s: numeric argument required\n", opt[1]);
			clear(shell);
			exit(2);
		}
		else if (g_global.minus && ft_strlen(opt[1]) > 19)
		{
			write(2, "exit\n", 6);
			ft_putstr_fderr("bash: exit: %s: numeric argument required\n", opt[1]);
			clear(shell);
			exit(2);
		}
		error = ft_atoi(opt[1]);
		if (error > 255 || error < 0)
		{
			write(2, "exit\n", 6);
			clear(shell);
			exit(error % 256);
		}
		write(2, "exit\n", 6);
		clear(shell);
		exit(error);
	}
	write(2, "exit\n", 6);
	clear(shell);
	exit(0);
}
