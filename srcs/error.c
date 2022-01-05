/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:16:14 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/05 14:23:56 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error_two(char *str, t_shell *shell, int error)
{
	(void)shell;
	if (error == 1)
	{
		printf("bash: syntax error near unexpected token `%s'\n", str);
		shell->error_dol = 258;
	}
	if (error == 2)
	{
		printf(">\n");
	}
	if (error == 3)
	{
		printf("bash: cd: %s: No such file or directory\n", str);
		shell->error_dol = 1;
		shell->on = 1;
	}
	if (error == 4)
	{
		printf("bash: export: `%s': not a valid identifier\n", str);
		shell->error_dol = 1;
	}
	if (error == 5)
	{
		printf("bash: unset: `%s': not a valid identifier\n", str);
		shell->error_dol = 1;
	}
	if (error == 6)
	{
		printf("NO ENV FOUND SORRY NEED TO QUIT %s\n", str);
		// shell->error_dol = 127;
		exit(127);
	}
	if (error == 7)
	{
		printf("%s", str);
		shell->error_dol = 1;
	}
	return (0);
}

	// Script end by ctrl-D -> 130
	// Fatal error signal comme kill -9 $PPID -> 128 + n
	// Mauvaise utilisation de shell builtin -> 2

	// if prompt /dev/null -> Permission denied Error message 126


	// ft_lstclear_shell(&shell->token);
	// ft_lstclear_action(&shell->action);
	// strerror(errno) plus tard