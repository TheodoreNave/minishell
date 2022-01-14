/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_for_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:34:22 by tnave             #+#    #+#             */
/*   Updated: 2022/01/14 18:08:23 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	make_token_lst_ext(t_shell *shell)
{
	shell->quote = 0;
	shell->simple_quote = 0;
	clear_buff(shell);
	return (ft_error_two(NULL, shell, 2));
}

int	make_token_lst(char *prompt, t_shell *shell)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			if (prompt[i] == 39)
				shell->simple_quote = 1;
			i += add_to_buff_quote(&prompt[i], prompt[i], shell);
			if (shell->quote == -1)
				return (make_token_lst_ext(shell));
		}
		else if (is_double_redir(prompt[i], prompt[i + 1]))
			i += add_to_buff_redir(prompt[i], shell);
		else if (!is_symbol(prompt[i]))
			add_to_buff_no_space(shell, prompt[i]);
		else if (is_symbol(prompt[i]))
			empty_buff_in_lst(shell, prompt[i]);
		i++;
	}
	if (prompt[i] == '\0')
		empty_buff_in_lst(shell, prompt[i]);
	return (1);
}
