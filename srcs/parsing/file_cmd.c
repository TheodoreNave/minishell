/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:24:23 by tnave             #+#    #+#             */
/*   Updated: 2021/12/16 15:55:25 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		fill_cmd(t_shell *shell)
{
	t_token_list *tmp;

	tmp = shell->token;
	while (tmp)
	{
		t_cmd_list *tpmp;
		tpmp = malloc(sizeof(t_cmd_list));
		if (!tpmp)
			return (0);
		ft_memset(tpmp, 0, sizeof(t_cmd_list));		// changer de place ??
		tpmp->next = NULL;
		if (is_type_redir(tmp->type))
		{
			if (!init_lst_redir(shell, &tmp, tpmp))
				break ;
		}
		else if (tmp->type == TYPE_PIPE)
		{
			tpmp->type_start = tmp->type;
			tpmp->type_end = tmp->type;
			ft_lstadd_back_action(&shell->action, tpmp);
		}
		else if (tmp->type == TYPE_WORD)
		{
			tpmp->type_start = tmp->type;
			malloc_opt(&tmp, tpmp);
			if (tmp)
			{
				tpmp->type_end = tmp->type;
				ft_lstadd_back_action(&shell->action, tpmp);
				tmp = tmp->prev;
			}
			else
			{
				tpmp->type_end = TYPE_END;
				ft_lstadd_back_action(&shell->action, tpmp);
				break ;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
