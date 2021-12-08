/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:33:27 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/08 19:47:12 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_list	*ft_lstnew_shell(int type, char *word)
{
	t_token_list	*new_list;

	new_list = malloc(sizeof(t_token_list));
	if (!(new_list))
		return (NULL);
	new_list->type = type;
	new_list->word = ft_strdup(word);
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back_shell(t_token_list **token, t_token_list *new)
{
	t_token_list	*tmp;

	if (!token || !new)
		return ;
	if (*token)
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->prev = tmp;
	}
	else
	{
		new->prev = NULL;
		*token = new;
	}
}

void	ft_lstclear_shell(t_token_list **token)
{
	t_token_list	*end_list;

	if (!token)
		return ;
	while (*token != NULL)
	{
		end_list = *token;
		if (end_list->word)
		{
			free(end_list->word);
			end_list->word = NULL;
		}
		*token = end_list->next;
		free(end_list);
	}
	*token = NULL;
}
