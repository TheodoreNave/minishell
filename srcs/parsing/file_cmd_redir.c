/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cmd_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:09:08 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/14 16:14:05 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_opt(t_token_list **tmp, t_cmd_list *tpmp)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lstsize_shell(*tmp);
	tpmp->opt = malloc(sizeof(char *) * (size + 1));
	if (!tpmp->opt)
		return ;
	while (i < size)
	{
		tpmp->opt[i] = ft_strdup((*tmp)->word);
		i++;
		*tmp = (*tmp)->next;
	}
	tpmp->opt[i] = NULL;
}

void	init_lst_one(t_shell *shell, t_token_list **tmp, t_cmd_list *tpmp)
{
	tpmp->type_end = (*tmp)->type;
	ft_lstadd_back_action(&shell->action, tpmp);
	*tmp = (*tmp)->prev;
}

void	init_lst_two(t_shell *shell, t_cmd_list *tpmp)
{
	tpmp->type_end = TYPE_END;
	ft_lstadd_back_action(&shell->action, tpmp);
}

int	init_lst_redir(t_shell *shell, t_token_list **tmp, t_cmd_list *tpmp)
{
	tpmp->type_start = (*tmp)->type;
	*tmp = (*tmp)->next;
	if (*tmp)
	{
		tpmp->fichier = ft_strdup((*tmp)->word);
		*tmp = (*tmp)->next;
		if (*tmp)
		{
			if ((*tmp)->type == TYPE_WORD)
				malloc_opt(tmp, tpmp);
			if (*tmp)
				init_lst_one(shell, tmp, tpmp);
			else
			{
				init_lst_two(shell, tpmp);
				return (0);
			}
		}
		else
		{
			init_lst_two(shell, tpmp);
			return (0);
		}
	}
	return (1);
}
