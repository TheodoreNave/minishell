/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:46:34 by tnave             #+#    #+#             */
/*   Updated: 2021/11/26 13:47:26 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

t_cmd_list	*ft_lstnew_action(t_cmd_list *commandes)
{
	t_cmd_list	*new_list;

	new_list = malloc(sizeof(t_cmd_list));
	if (!(new_list))
		return (NULL);
	new_list->typetype = commandes->typetype;
	new_list->cmd = ft_strdup(commandes->cmd);
	new_list->opt = commandes->opt;
	new_list->fichier = ft_strdup(commandes->fichier);
	new_list->next = NULL;
	return (new_list);
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

int	ft_lstsize_shell(t_token_list *lst)
{
	int		i;
	t_token_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}