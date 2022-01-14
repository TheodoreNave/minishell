/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_for_token_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:01:17 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/14 18:01:41 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ')
		return (1);
	return (0);
}

void	add_symbol(t_shell *shell, char symbole)
{
	if (symbole == '|')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_PIPE, "|"));
	else if (symbole == '<')
		ft_lstadd_back_shell(&shell->token,
			ft_lstnew_shell(TYPE_REDIR_LEFT, "<"));
	else if (symbole == '>')
		ft_lstadd_back_shell(&shell->token,
			ft_lstnew_shell(TYPE_REDIR_RIGHT, ">"));
	else if (symbole == 39)
		ft_lstadd_back_shell(&shell->token,
			ft_lstnew_shell(TYPE_SIMPLE_QUOTE, "\'"));
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
		ft_lstadd_back_shell(&shell->token,
			ft_lstnew_shell(TYPE_HEREDOC, "<<"));
	else if (c == '>')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_REDIR, ">>"));
	return (1);
}
