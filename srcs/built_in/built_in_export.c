/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:07:23 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/24 13:41:47 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_alpha(char c)
{
	if (!((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c == '_')))
		return (0);
	return (1);
}

int	check_name_variable(char *str, t_shell *shell, int j)
{
	int i;

	i = 0;
	if (!check_is_alpha(str[i]) || (str[i] >= '0' && str[i] <= '9'))
	{
		ft_error_two(str, shell, j);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!check_is_alpha(str[i]) && !(str[i] >= '0' && str[i] <= '9'))
		{
			ft_error_two(str, shell, j);
			return (1);
		}
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	check_var_in_env(t_env *env, char *opt)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if ((ft_strncmpp(tmp->var_env, opt, ft_strlen_char(opt, '=')) == 0))
		{
			free(tmp->var_env);
			tmp->var_env = strdup(opt);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	built_in_export(char **opt, t_env *environ, t_shell *shell)
{
	printf("JE SUIS  DANS EXPORT\n");
	int i;
	int j;

	i = 1;
	j = 0;
	if (!opt[1])
	{
		print_sort_env(environ);
		return (0);
	}
	while (opt[i])
	{
		if (check_var_in_env(environ, opt[i]))
		{
			if (check_name_variable(opt[i], shell, 4))
				return (1);
			while (opt[i][j])
			{
				if (opt[i][j] == '=')
				{
					ft_lstadd_back_env(&environ, ft_lstnew_env(opt[i]));
				}
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
