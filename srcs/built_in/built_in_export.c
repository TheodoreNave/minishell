/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:07:23 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/09 01:38:36 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 	not_valid_export(char c)
{
	if (!((c >= 97 && c <= 122) || (c >= 65 && c <= 90)))
		return (0);
	return (1);
}

// fix export the.o=ok c'est une erreur + export/unset sans argument + et theo+=ok aussi

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