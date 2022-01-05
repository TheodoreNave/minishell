/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:55:47 by tnave             #+#    #+#             */
/*   Updated: 2022/01/05 14:12:32 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_exit(t_shell *shell)
{
	if (shell->environ)
		ft_lstclear_env(&shell->environ);
	if (shell->action)
		ft_lstclear_action(&shell->action);
	if (shell->dol)
		ft_lstclear_dol(&shell->dol);
	printf("exit\n");
	exit(0);
	// calcul a faire en fonction de l'exit si non compries entre 0 et 255 sinon renvoyer valeur entre 0 et 255
}