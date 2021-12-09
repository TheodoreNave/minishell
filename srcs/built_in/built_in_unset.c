/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:28:41 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/09 00:58:58 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_unset(t_shell *shell, char **opt)
{
	t_env *tmp;

	tmp = shell->environ;

	int i;

	i = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, opt[1], ft_strlen(opt[1])) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = strdup("");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}