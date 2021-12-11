/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:52:31 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/11 18:13:01 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dol	*ft_lstnew_dol(char *word)
{
	t_dol	*new_list;

	new_list = malloc(sizeof(t_dol));
	if (!(new_list))
		return (NULL);
	new_list->word_dol = word;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back_dol(t_dol **dol, t_dol *new)
{
	t_dol	*tmp;

	if (!dol || !new)
		return ;
	if (*dol)
	{
		tmp = *dol;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->prev = tmp;
	}
	else
	{
		new->prev = NULL;
		*dol = new;
	}
}

void	ft_lstclear_dol(t_dol **dol)
{
	t_dol	*end_list;

	if (!dol)
		return ;
	while (*dol != NULL)
	{
		end_list = *dol;
		if (end_list->word_dol)
		{
			free(end_list->word_dol);
			end_list->word_dol = NULL;
		}
		*dol = end_list->next;
		free(end_list);
	}
	*dol = NULL;
}
