/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:23:56 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/10 14:35:30 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt(t_shell *shell, char *buff)
{
	char *temp;
	char *join_temp;

	if (!shell->on) // shell->on == 0
	{
		// free shell->pwd_temp ???
		shell->pwd_temp = getcwd(shell->buff_pwd, sizeof(shell->buff_pwd));
		if (!shell->pwd_temp)
			free(shell->pwd_temp);
	}
	if (shell->on)
	{
		join_temp = ft_strjoin(shell->pwd_temp, " $> ");
		buff = readline(join_temp);
		free(join_temp);
		shell->on = 0;
	}
	else
	{
		temp = getcwd(shell->buff_pwd, sizeof(shell->buff_pwd));
		if (!temp)
			free(temp);
		join_temp = ft_strjoin(temp , " $> ");
		buff = readline(join_temp);
		free(join_temp);
	}
	if (!buff)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	shell->on = 0;
	return (buff);
}
