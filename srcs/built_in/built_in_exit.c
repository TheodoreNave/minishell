/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:47 by tnave             #+#    #+#             */
/*   Updated: 2022/01/06 19:25:46 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_exit(t_shell *shell, char **opt)
{
	int i;

	i = 0;
	// Arguments replace 0 par opt[1];
	if (shell->environ)
		ft_lstclear_env(&shell->environ);
	if (shell->action)
		ft_lstclear_action(&shell->action);
	if (shell->dol)
		ft_lstclear_dol(&shell->dol);
	if (i > 255)
		exit(128);
	else if (i < 0)
		exit(128);
	if (opt[1])
	{
		// if ! check_is_digit(opt[1]) sinon bash: exit: opt[1]: numeric argument required
		// 	exit(255);
		// if ! atoi(opt[1]) > 255 || atoi(opt[1]) < 0 
		// 	exit(atoi(opt[1]) % 256);
		// exit(atoi(opt[1]))
	}
	printf("exit\n");
	exit(0);
	// calcul a faire en fonction de l'exit si non compries entre 0 et 255 sinon renvoyer valeur entre 0 et 255
}
