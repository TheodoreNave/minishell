/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:46:34 by tnave             #+#    #+#             */
/*   Updated: 2021/12/08 19:46:50 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_lstnew_env(char *variable)
{
	t_env	*new_list;

	new_list = malloc(sizeof(t_env));
	if (!(new_list))
		return (NULL);
	new_list->var_env = ft_strdup(variable);
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back_env(t_env **environ, t_env *new)
{
	t_env	*tmp;

	if (!environ || !new)
		return ;
	if (*environ)
	{
		tmp = *environ;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->prev = tmp;
	}
	else
	{
		new->prev = NULL;
		*environ = new;
	}
}

int	ft_lstsize_shell(t_token_list *lst)
{
	int		i;
	t_token_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL && tmp->type == TYPE_WORD)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}