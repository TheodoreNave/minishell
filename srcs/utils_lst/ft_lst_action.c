/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:32:07 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/10 20:09:23 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back_action(t_cmd_list **action, t_cmd_list *new)
{
	t_cmd_list	*tmp;

	if (!action || !new)
		return ;
	if (*action)
	{
		tmp = *action;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->prev = tmp;
	}
	else
	{
		new->prev = NULL;
		*action = new;
	}
}

void	ft_lstclear_action(t_cmd_list **action)
{
	t_cmd_list	*temp;

	if (!action)
		return ;
	while (*action != NULL)
	{
		temp = *action;
		if (temp->fichier)
		{
			free(temp->fichier);
			temp->fichier = NULL;
		}
		if (temp->opt)
		{
			free_split(temp->opt);
			temp->opt = NULL;
		}
		*action = temp->next;
		free(temp);
	}
	*action = NULL;
}