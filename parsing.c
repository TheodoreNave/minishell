/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:34:22 by tnave             #+#    #+#             */
/*   Updated: 2021/11/29 17:27:58 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$' || c == ' ')
		return (1);
	return (0);
}

void	add_to_buff_no_space(t_shell *shell, char c)
{
	if (c != ' ')
	{
		shell->buff_temp[shell->x] = c;
		shell->x++;
	}
	return ;
}

void	add_to_buff(t_shell *shell, char c)
{
	shell->buff_temp[shell->x] = c;
	shell->x++;
	return ;
}


void	clear_buff(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->buff_temp[i])
	{
		shell->buff_temp[i] = '\0';
		i++;
	}
	return ;
}

void		add_symbol(t_shell *shell, char symbole)
{
	if (symbole == '|')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_PIPE, "|"));
	else if (symbole == '<')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_REDIR, "<"));
	else if (symbole == '>')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_REDIR, ">"));
	else if (symbole == '$')
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_DOLLARS, "$"));
	else if (symbole == 34)
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_DOUBLE_QUOTE, "\""));
	else if (symbole == 39)
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_SIMPLE_QUOTE, "\'"));
	return ;
}

void	empty_buff_in_lst(t_shell *shell, char symbole)
{
	if (ft_strlen(shell->buff_temp) > 0)
	{
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_WORD, shell->buff_temp));
		clear_buff(shell);
		shell->x = 0;
	}
	if (is_symbol(symbole))
	{
		add_symbol(shell, symbole);
	}
	return ;
}

int	add_to_buff_quote(char *prompt, char c, t_shell *shell)
{
	int i = 1;
	printf("i = %d\n", i);
	printf("prompt = [%s]\n", prompt);
	if (c == '\0')
		return 0;
	while (prompt[i] && prompt[i] != c)
	{
		add_to_buff(shell, prompt[i]);
		i++;
	}
	// empty_buff_in_lst(shell, 0);
	return (i);
}

int	parsing_shit(char *prompt, t_shell *shell)
{
	int i = 0;
	int quote = 0;
	while (prompt[i])
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			// i += add_to_buff_quote(&prompt[i], prompt[i], shell);
			quote = quote ? 0 : 1;
		}
		else if (!is_symbol(prompt[i]))
		{
			if (quote)
				add_to_buff(shell, prompt[i]);
			else
				add_to_buff_no_space(shell, prompt[i]);
		} 
		else if (is_symbol(prompt[i]) && !quote)
		{
			empty_buff_in_lst(shell, prompt[i]);
		}
		i++;
	}
	if (prompt[i] == '\0')
	{
		empty_buff_in_lst(shell, prompt[i]);
	}
	return (0);
}
