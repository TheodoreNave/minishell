/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:21:10 by tnave             #+#    #+#             */
/*   Updated: 2022/01/06 16:47:11 by tnave            ###   ########.fr       */
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
	char *buf;

	buf = NULL;
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
			return (ft_error_two(tmp->word, shell, 1));
			// buf = readline(">");
			// ft_strjoin()
			// rl_on_new_line();
			// rl_replace_line(">\n", 0);
			// rl_redisplay();
			// rl_replace_line(">\n");
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