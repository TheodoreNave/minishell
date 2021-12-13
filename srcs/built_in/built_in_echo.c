/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:20 by tnave             #+#    #+#             */
/*   Updated: 2021/12/13 18:05:56 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		built_in_echo(char **opt, t_shell *shell)
{
	int i = 0;
	if (!opt)
		return (0);
	if (!strncmp(opt[i], "$?", 3))
		printf("carre = [%d]", shell->dol->question_dol);
	while (opt[i])
	{
		write(1, opt[i], ft_strlen(opt[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int		built_in_echo_n(char **opt, t_shell *shell)
{
	int i;

	i = 0;
	if (!opt)
		return (0);
	if (!strncmp(opt[i], "$?", 3))
		printf("%d", shell->dol->question_dol);
	while (opt[i])
	{
		write(1, opt[i], ft_strlen(opt[i]));
		write(1, " ", 1);
		i++;
	}
	return (0);
}