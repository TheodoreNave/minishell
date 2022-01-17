/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:24:23 by tnave             #+#    #+#             */
/*   Updated: 2022/01/17 17:19:08 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_cmd_pipe(t_shell *shell, t_token_list *tmp, t_cmd_list *tpmp)
{
	tpmp->type_start = tmp->type;
	tpmp->type_end = tmp->type;
	ft_lstadd_back_action(&shell->action, tpmp);
	return ;
}

int	fill_cmd_two(t_shell *shell, t_token_list *tmp, t_cmd_list *tpmp)
{
	if (!tmp)
	{
		tpmp->type_end = TYPE_END;
		ft_lstadd_back_action(&shell->action, tpmp);
		return (0);
	}
	tpmp->type_end = tmp->type;
	ft_lstadd_back_action(&shell->action, tpmp);
	return (1);
}

int	fill_cmd_redir(t_shell *shell, t_token_list *tmp, t_cmd_list *tpmp)
{
	if (is_type_redir(tmp->type))
	{
		if (!init_lst_redir(shell, &tmp, tpmp))
			return (0);
	}
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
		if (!tpmp)
			return (0);
		ft_memset(tpmp, 0, sizeof(t_cmd_list));
		if (!fill_cmd_redir(shell, tmp, tpmp))
			break ;
		else if (tmp->type == TYPE_PIPE)
			fill_cmd_pipe(shell, tmp, tpmp);
		else if (tmp->type == TYPE_WORD)
		{
			tpmp->type_start = tmp->type;
			malloc_opt(&tmp, tpmp);
			if (!fill_cmd_two(shell, tmp, tpmp))
				break ;
			tmp = tmp->prev;
		}
		tmp = tmp->next;
	}
	return (0);
}
