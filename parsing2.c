/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:21:10 by tnave             #+#    #+#             */
/*   Updated: 2021/11/26 17:17:31 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void parsing_shit_two(t_shell *shell)
{
	shell->i = 0;
	char 	**temp;
	t_token_list *tmp;

	tmp = shell->token;
	t_cmd_list *tmpp;
	tmpp = malloc(sizeof(t_cmd_list));
	if (!tmpp)
		return ;
	tmpp->next = NULL;
	
	
	if ((tmp->type == TYPE_REDIR) && tmp->next)
	{
		if (tmp->next->type == TYPE_WORD)
		{
			while (tmp->next->word[shell->i] == ' ')
				shell->i++;
			while (tmp->next->word[shell->i] != ' ' && tmp->next->word[shell->i] != '\0')
			{
				add_to_buff(shell, tmp->next->word[shell->i]);
				shell->i++;
			}
			tmpp->type_start = TYPE_REDIR_LEFT;
			tmpp->fichier = strdup(shell->buff_temp);
			temp = ft_split(&tmp->next->word[shell->i], ' ');
			tmpp->cmd = strdup(temp[0]);
			tmpp->opt = temp;
			if (tmp->next->next)
			{
				if (tmp->next->next->type >= 2 && tmp->next->next->type <= 8)
					tmpp->type_end = tmp->next->next->type;
				// else if (tmp->next->next->type == 9)
				// {
				// 	//fonction env
				// }
			}
			else 
				tmpp->type_end = TYPE_END;
		}	
		else
			exit(1);
		ft_lstadd_back_action(&shell->action, tmpp);
	}
	clear_buff(shell);
	shell->x = 0;
}
