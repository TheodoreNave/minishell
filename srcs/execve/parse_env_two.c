/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:18:40 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/17 14:20:07 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_env_ext_one(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->new_env_tab[i])
	{
		if (ft_strncmp(shell->new_env_tab[i], "PATH=", 5) == 0)
		{
			shell->parse_env = ft_split(is_slash(shell->new_env_tab[i]), ':');
			break ;
		}
		i++;
	}
	return ;
}

int	parse_env_two(t_shell *shell)
{
	int	i;

	i = 0;
	parse_env_ext_one(shell);
	while ((shell->parse_env && shell->parse_env[i])
		&& (ft_strchr(shell->opt2[0], '/')))
	{
		shell->join = ft_strjoin_three(shell->parse_env[i],
				"/", shell->opt2[0]);
		if (access(shell->join, F_OK) == 0)
		{
			break ;
		}
		i++;
		free(shell->join);
		shell->join = NULL;
	}
	if (!shell->join)
		shell->join = ft_strdup(shell->opt2[0]);
	if (shell->parse_env)
	{
		free_split(shell->parse_env);
		shell->parse_env = NULL;
	}
	return (0);
}
