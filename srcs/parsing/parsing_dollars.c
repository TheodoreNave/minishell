/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:20:59 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/19 17:39:54 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing_dollars_ext(t_shell *shell)
{
	t_token_list	*tmp;

	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == TYPE_SIMPLE_QUOTE)
		{
			tmp->type = TYPE_WORD;
		}
		tmp = tmp->next;
	}
	return ;
}

void	make_simple_quote(t_token_list *tmp)
{
	tmp->next->type = TYPE_SIMPLE_QUOTE;
	return ;
}

int	parsing_dollars(t_shell *shell)
{
	t_token_list	*tmp;

	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == TYPE_HEREDOC && tmp->next->type == TYPE_WORD)
			make_simple_quote(tmp);
		if (tmp->type == TYPE_WORD)
		{
			if (check_dollars(tmp->word))
			{
				new_token_dollars(tmp->word, shell);
				recup_dollars(shell);
				if (tmp->word)
					free(tmp->word);
				tmp->word = join_dollars(shell);
				if (shell->dol)
					ft_lstclear_dol(&shell->dol);
			}
		}
		tmp = tmp->next;
	}
	parsing_dollars_ext(shell);
	return (0);
}
