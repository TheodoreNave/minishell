/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:34:22 by tnave             #+#    #+#             */
/*   Updated: 2021/11/26 15:08:58 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>'
		|| c == '$' || c == 34 || c == 39)
		return (1);
	return (0);
}

void	add_to_buff(t_shell *shell, char c)
{
	// printf("%c\n", c);
	shell->buff_temp[shell->x] = c;
	shell->x++;
}

void	add_to_buff_two(t_shell *shell, char c)
{
	// printf("%c\n", c);
	shell->buff_two[shell->x] = c;
	shell->x++;
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

void	clear_buff_two(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->buff_two[i])
	{
		shell->buff_two[i] = '\0';
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
}

int	parsing_shit(char *prompt, t_shell *shell)
{
	int i = 0;
	while (prompt[i])
	{
		if (!is_symbol(prompt[i]))
		{
			add_to_buff(shell, prompt[i]);
		}
		if (is_symbol(prompt[i]))
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
