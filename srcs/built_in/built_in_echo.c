/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:20 by tnave             #+#    #+#             */
/*   Updated: 2022/01/12 18:41:48 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_n(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_echo(char **opt, t_shell *shell)
{
	int i;

	i = 1;
	if (opt[1])
	{
		if (!check_if_n(opt[i]))
		{
			while (!check_if_n(opt[i]))
				i++;
			built_in_echo_n(&opt[i], shell);
		}
		else
			built_in_echo(&opt[1], shell);
	}
	else
		write(1, "\n", 1);
}

int	built_in_echo(char **opt, t_shell *shell)
{
	int	i;

	i = 0;
	(void)shell;
	while (opt[i])
	{
		if (write(1, opt[i], ft_strlen(opt[i])) == -1)
		{
			ft_putstr_fderr("bash: echo: write error: %s\n", strerror(errno));
			clear(shell);
			exit(1);
		}
		if (!(opt[i + 1] == NULL))
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
		if (write(1, opt[i], ft_strlen(opt[i])) == -1)
		{
			ft_putstr_fderr("bash: echo: write error: %s\n", strerror(errno));
			clear(shell);
			exit(1);
		}
		if (!(opt[i + 1] == NULL))
			write(1, " ", 1);
		i++;
	}
	return (0);
}
