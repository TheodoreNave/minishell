/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:24:23 by tnave             #+#    #+#             */
/*   Updated: 2022/01/18 18:43:18 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fill_cmd_ext(t_shell *shell, t_token_list **tmp, t_cmd_list **tpmp)
{
	malloc_opt(tmp, (*tpmp));
	if ((*tmp))
	{
		(*tpmp)->type_end = (*tmp)->type;
		ft_lstadd_back_action(&shell->action, (*tpmp));
		(*tmp) = (*tmp)->prev;
	}
	else
	{
		(*tpmp)->type_end = TYPE_END;
		ft_lstadd_back_action(&shell->action, (*tpmp));
		return (0);
	}
	return (1);
}

void	fill_cmd_ext_one(t_shell *shell, t_token_list **tmp, t_cmd_list **tpmp)
{
	(*tpmp)->type_start = (*tmp)->type;
	(*tpmp)->type_end = (*tmp)->type;
	ft_lstadd_back_action(&shell->action, (*tpmp));
}

int	check_tpmp(t_cmd_list *tpmp)
{
	if (!tpmp)
		return (0);
	ft_memset(tpmp, 0, sizeof(t_cmd_list));
	return (1);
}

int	fill_cmd(t_shell *shell)
{
	t_token_list	*tmp;
	t_cmd_list		*tpmp;

	tmp = shell->token;
	while (tmp)
	{
		tpmp = malloc(sizeof(t_cmd_list));
		if (!check_tpmp(tpmp))
			return (0);
		if (is_type_redir(tmp->type))
		{
			if (!init_lst_redir(shell, &tmp, tpmp))
				break ;
		}
		else if (tmp->type == TYPE_PIPE)
			fill_cmd_ext_one(shell, &tmp, &tpmp);
		else if (tmp->type == TYPE_WORD)
		{
			tpmp->type_start = tmp->type;
			if (!fill_cmd_ext(shell, &tmp, &tpmp))
				break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
