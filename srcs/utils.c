/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 01:58:05 by tnave             #+#    #+#             */
/*   Updated: 2021/12/12 14:10:37 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void		empty_buff_in_lst(t_shell *shell, char symbole)
{
	if (shell->simple_quote == 1)
	{
		if (ft_strlen(shell->buff_temp) > 0)
		{
			ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_SIMPLE_QUOTE, shell->buff_temp));
			clear_buff(shell);
			shell->x = 0;
			shell->simple_quote = 0;
		}
	}
	// if shell->double_quote ?
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
	int i;

	i = 1;
	if (c == '\0')
		return 0;
	if (prompt[i] == c)
		ft_lstadd_back_shell(&shell->token, ft_lstnew_shell(TYPE_WORD, ""));
	while (prompt[i] && prompt[i] != c)
	{
		add_to_buff(shell, prompt[i]);
		i++;
	}
	if (prompt[i] != c)
		shell->quote = -1;
	return (i);
}

int	ft_strlen_egal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}