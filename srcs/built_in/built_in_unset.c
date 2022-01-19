/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:28:41 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/14 14:36:20 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	boucle_unset(t_shell *shell, char *opt)
{
	t_env	*tmp;

	tmp = shell->environ;
	while (tmp)
	{
		if ((ft_strncmp(tmp->var_env, opt, ft_strlen(opt)) == 0)
			&& (tmp->var_env[(int)ft_strlen(opt)] == '='))
		{
			free(tmp->var_env);
			tmp->var_env = ft_strdup("");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	built_in_unset(t_shell *shell, char **opt)
{
	int	i;

	i = 1;
	while (opt[i])
	{
		if (!boucle_unset(shell, opt[i]))
		{
			if (!check_name_variable(opt[i], shell, 5))
				ft_error_two(opt[i], shell, 5);
		}
		i++;
	}
	return (0);
}
