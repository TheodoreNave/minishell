/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:47 by tnave             #+#    #+#             */
/*   Updated: 2022/01/06 18:14:38 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_exit(t_shell *shell)
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
	printf("exit\n");
	exit(5);
	// calcul a faire en fonction de l'exit si non compries entre 0 et 255 sinon renvoyer valeur entre 0 et 255
}
