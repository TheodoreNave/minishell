/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_convert_dol_herdoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:32:18 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/17 13:23:50 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	convert_dol_her_ext(char *str, t_shell *shell, long *j)
{
	t_env	*tmp;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen_space(str);
	tmp = shell->environ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, str, size) == 0)
		{
			if (tmp->var_env[size] == '=')
			{
				while (tmp->var_env[size + 1 + i])
				{
					add_to_buff_king(shell, tmp->var_env[size + 1 + i], j);
					i++;
				}
			}
			else
				add_to_buff_king(shell, 0, j);
		}
		tmp = tmp->next;
	}
	return (size);
}

int	convert_dol_her(char *str, t_shell *shell, long *j)
{
	char	*dol_temp;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen_space(str);
	if (str[0] == '?')
	{
		dol_temp = ft_itoa(g_global.error_dollars);
		while (dol_temp[i])
		{
			add_to_buff_king(shell, dol_temp[i], j);
			i++;
		}
		free(dol_temp);
		dol_temp = NULL;
		return (1);
	}
	if (size == 0)
	{
		add_to_buff_king(shell, '$', j);
		return (0);
	}
	return (convert_dol_her_ext(str, shell, j));
}

int	parse_dollars_heredoc(char *str, t_shell *shell, char *tmp)
{
	long	j;
	int		i;

	i = 0;
	j = 0;
	if (!str)
	{
		ft_error_two(tmp, shell, 8);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '$' && (!(is_whitespace(str[i + 1]))))
			i += convert_dol_her(&str[i + 1], shell, &j) + 1;
		else
		{
			add_to_buff_king(shell, str[i], &j);
			i++;
		}
	}
	return (0);
}
