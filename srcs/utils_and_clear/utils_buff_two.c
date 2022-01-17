/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_buff_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:52:12 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/17 16:54:17 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_to_buff_no_space(t_shell *shell, char c)
{
	if (c != ' ')
	{
		shell->buff_temp[shell->x] = c;
		shell->x++;
	}
	return ;
}

void	add_to_buff_king(t_shell *shell, char c, long *j)
{
	shell->buffer_king[*j] = c;
	(*j)++;
	return ;
}

void	add_to_buff(t_shell *shell, char c)
{
	shell->buff_temp[shell->x] = c;
	shell->x++;
	return ;
}

void	clear_buffer_king(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->buffer_king[i])
	{
		shell->buffer_king[i] = '\0';
		i++;
	}
	return ;
}

void	clear_buff(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->buff_temp[i])
	{
		shell->buff_temp[i] = '\0';
		i++;
	}
	return ;
}
