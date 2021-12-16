/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_for_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:34:22 by tnave             #+#    #+#             */
/*   Updated: 2021/12/16 16:30:06 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ')
		return (1);
	return (0);
}

void		add_symbol(t_shell *shell, char symbole)
{
	if (symbole == '|')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_PIPE, "|"));
	else if (symbole == '<')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_REDIR_LEFT, "<"));
	else if (symbole == '>')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_REDIR_RIGHT, ">"));
	else if (symbole == 39)
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_SIMPLE_QUOTE, "\'"));
	return ;
}

int	is_double_redir(char a, char b)
{
	if (a == '<' && b == '<')
		return (1);
	else if (a == '>' && b == '>')
		return (1);
	return (0);
}

int	add_to_buff_redir(char c, t_shell *shell)
{
	if (c == '<')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_HEREDOC, "<<"));
	else if (c == '>')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_REDIR, ">>"));
	return (1);
}

int	make_token_lst(char *prompt, t_shell *shell)
{
	int i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			if (prompt[i] == 39)
				shell->simple_quote = 1;
			i += add_to_buff_quote(&prompt[i], prompt[i], shell);
			if (shell->quote == -1)
				return (ft_error_two(NULL, shell, 2));
		}
		else if (is_double_redir(prompt[i], prompt[i + 1]))
		{
			i += add_to_buff_redir(prompt[i], shell);
		}
		else if (!is_symbol(prompt[i]))
		{
			add_to_buff_no_space(shell, prompt[i]);
		}
		else if (is_symbol(prompt[i]))
		{
			empty_buff_in_lst(shell, prompt[i]);
		}
		i++;
	}
	if (prompt[i] == '\0')
	{
		empty_buff_in_lst(shell, prompt[i]);
	}
	return (1);
}
