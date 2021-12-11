/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:28:41 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/11 20:28:08 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_unset(t_shell *shell, char **opt)
{
	//MULTI UNSET ERROR CARCTERE NON ALPHABETIQUE
	t_env *tmp;

	tmp = shell->environ;

	int i;

	i = 0;
	while (tmp)
	{
		if ((ft_strncmp(tmp->var_env, opt[1], ft_strlen(opt[1])) == 0)
			&& (tmp->var_env[(int)ft_strlen(opt[1])] == '='))
		{
			free(tmp->var_env);
			tmp->var_env = strdup("");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

// TIMOTHEE=98

// TIMOTHEE=42