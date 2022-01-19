/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:40:24 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/17 15:40:49 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_buff(char *buff)
{
	free(buff);
	buff = NULL;
	return ;
}

char	*prompt_ext_one(t_shell *shell, char *buff)
{
	buff = readline(">\n");
	shell->prompt = 0;
	return (buff);
}
