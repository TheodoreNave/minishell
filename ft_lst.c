/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:46:34 by tnave             #+#    #+#             */
/*   Updated: 2021/11/25 14:59:01 by tnave            ###   ########.fr       */
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
	t_token_list	*end_list;

	if (!token || !new)
		return ;
	if (*token)
	{
		end_list = *token;
		while (end_list->next != NULL)
			end_list = end_list->next;
		end_list->next = new;
	}
	else
		*token = new;
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