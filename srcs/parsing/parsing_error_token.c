/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:21:10 by tnave             #+#    #+#             */
/*   Updated: 2022/01/05 13:23:12 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_type_redir(int type)
{
	if (type == TYPE_REDIR || type == TYPE_REDIR_LEFT
		|| type == TYPE_REDIR_RIGHT || type == TYPE_HEREDOC)
		return (1);
	return (0);
}

int parsing_errors_token(t_shell *shell)
{
	t_token_list *tmp;

	tmp = shell->token;
	while (tmp)
	{
		if (is_type_redir(tmp->type) && tmp->next)
		{
			if (tmp->next->type == TYPE_PIPE || is_type_redir(tmp->next->type))
				return (ft_error_two(tmp->next->word, shell, 1));
		}
		else if (tmp->type == TYPE_PIPE && tmp->prev == NULL)
		{
			return(ft_error_two(tmp->word, shell, 1));
			// Error message 258 need modulo
		}
		else if (tmp->type == TYPE_PIPE && tmp->next)
		{
			if (tmp->next->type == TYPE_PIPE)
				return (ft_error_two(tmp->next->word, shell, 1));
			// Error message 258 need modulo

		}
		else if (tmp->type == TYPE_PIPE && tmp->next == NULL)
		{
			printf(">\n");
			return (0);
			// Display new line ?
		}
		else if (is_type_redir(tmp->type) && tmp->next == NULL)
		{
			return (ft_error_two("newline", shell, 1));
			// Error message 258 need modulo
		}
		tmp = tmp->next;
	}
	return (1);
}