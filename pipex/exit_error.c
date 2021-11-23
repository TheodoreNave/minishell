/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:38:55 by tnave             #+#    #+#             */
/*   Updated: 2021/11/23 16:31:19 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(int i, char *str, t_utils *utils)
{
	if (i == 0)
	{
		write(2, str, ft_strlen(str));
		if (!utils->invalid_fd)
		{
			strerror(errno);
		}
	}
	if (i == 1)
	{
		if (utils->parse_env)
			free_split(utils->parse_env);
		ft_lstclear(&utils->lst, free);
		free_split(utils->temp);
	}
	if (i == 3)
	{
		write(2, str, ft_strlen(str));
		exit(0);
	}
	exit_function(utils);
}

void	exit_function(t_utils *utils)
{
	if (utils->parse_env)
	{
		free_split(utils->parse_env);
		utils->parse_env = NULL;
	}
	if (utils->lst)
	{
		ft_lstclear(&utils->lst, free);
		utils->lst = NULL;
	}
	// exit(0);
	// printf("cocuou\n");
	return ;
}
