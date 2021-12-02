/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:21:10 by tnave             #+#    #+#             */
/*   Updated: 2021/12/02 15:39:31 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_error_two(char *str, t_shell *shell, int error)
{
	(void)shell;
	if (error == 1)
	{
		printf("bash: syntax error near unexpected token `%s'\n", str);
	}
	if (error == 2)
	{
		printf(">\n");
	}
	ft_lstclear_shell(&shell->token);
	// ft_lstclear_action(&shell.action);
	// strerror(errno) tard plus
	return (0);
}

int parsing_shit_two(t_shell *shell)
{
	t_token_list *tmp;

	tmp = shell->token;
	while (tmp)
	{
		if ((tmp->type == TYPE_REDIR_LEFT || tmp->type == TYPE_REDIR_RIGHT) && tmp->next)
		{
			if (tmp->next->type == TYPE_PIPE || tmp->next->type == TYPE_REDIR_LEFT || tmp->next->type == TYPE_REDIR_RIGHT)
				return (ft_error_two(tmp->next->word, shell, 1));
		}
		else if (tmp->type == TYPE_PIPE && tmp->prev == NULL)
		{
			return(ft_error_two(tmp->word, shell, 1));
		}
		else if (tmp->type == TYPE_PIPE && tmp->next)
		{
			if (tmp->next->type == TYPE_PIPE)
				return (ft_error_two(tmp->next->word, shell, 1));
		}
		else if (tmp->type == TYPE_PIPE && tmp->next == NULL)
		{
			printf(">\n");
			return (0);
		}
		else if ((tmp->type == TYPE_REDIR_LEFT || tmp->type == TYPE_REDIR_RIGHT) && tmp->next == NULL)
		{
			return (ft_error_two("newline", shell, 1));
		}
		tmp = tmp->next;
	}
	return (1);
}