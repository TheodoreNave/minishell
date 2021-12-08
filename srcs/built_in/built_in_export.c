/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:07:23 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/08 20:32:54 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <linux/limits.h>

int 	not_valid_export(char c)
{
	if (!((c >= 97 && c <= 122) || (c >= 65 && c <= 90)))
		return (0);
	return (1);
}

// fix export the.o=ok c'est une erreur 

int 	built_in_export(char **opt, t_env *environ, t_shell *shell)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (opt[i])
	{
		if (!not_valid_export(opt[i][j]))
		{
			ft_error_two(opt[i], shell, 4);
			return (1);
		}
		while (opt[i][j])
		{
			if (opt[i][j] == '=')
			{
				if (opt[i][j + 1] != '\0' && opt[i][j + 1] != '=')
				{
					ft_lstadd_back_env(&environ, ft_lstnew_env(opt[i]));
					return (0);
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}