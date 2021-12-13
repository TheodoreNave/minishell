/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:16:14 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/13 16:48:40 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error_two(char *str, t_shell *shell, int error)
{
	(void)shell;
	if (error == 1)
	{
		printf("bash: syntax error near unexpected token `%s'\n", str);
	}
	if (error == 2)
	{
		printf(">\n");
	}
	if (error == 3)
	{
		printf("bash: cd: %s: No such file or directory\n", str);
		shell->on = 1;
	}
	if (error == 4)
	{
		printf("bash: export: `%s': not a valid identifier\n", str);
	}
	if (error == 5)
	{
		printf("bash: unset: `%s': not a valid identifier\n", str);
	}
	// ft_lstclear_shell(&shell->token);
	// ft_lstclear_action(&shell->action);
	// strerror(errno) plus tard
	return (0);
}