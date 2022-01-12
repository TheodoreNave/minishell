/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:20:59 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/12 12:15:36 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*dollars_question(char *word)
{
	char	*temp;
	char	*temporary;

	temp = NULL;
	temp = ft_itoa(g_global.error_dollars);
	temporary = ft_strjoin(temp, word);
	free(temp);
	return (temporary);
}

char	*join_dollars(t_shell *shell)
{
	t_dol	*tmp;
	char	*new_str;
	char	*temp;

	new_str = ft_strdup("");
	temp = NULL;
	tmp = shell->dol;
	while (tmp)
	{
		temp = new_str;
		new_str = ft_strjoin(new_str, tmp->word_dol);
		free(temp);
		tmp = tmp->next;
	}
	return (new_str);
}

char	*convert_dollars(char *word, t_shell *shell)
{
	t_env		*tmp;
	int			size;
	char		*join;

	tmp = shell->environ;
	size = ft_strlen_space(word);
	join = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, word, size) == 0)
		{
			if ((tmp->var_env[size] = '='))
				join = ft_strjoin(&tmp->var_env[size + 1], &word[size]);
			else
				join = ft_strjoin("", &word[size]);
			return (join);
		}
		tmp = tmp->next;
	}
	return (ft_strjoin("", &word[size]));
}

void	recup_dollars(t_shell *shell)
{
	t_dol	*tmp;
	char	*temporary;

	temporary = NULL;
	tmp = shell->dol;
	while (tmp)
	{
		if (tmp->word_dol[0] == '$' && tmp->word_dol[1] == '?')
		{
			temporary = dollars_question(&tmp->word_dol[2]);
			free(tmp->word_dol);
			tmp->word_dol = temporary;
		}
		else if (tmp->word_dol[0] == '$' && !ft_isalnum(tmp->word_dol[1]
				&& tmp->word_dol[1] != '\0'))
		{
			temporary = convert_dollars(&tmp->word_dol[1], shell);
			if (temporary != NULL)
			{
				free(tmp->word_dol);
				tmp->word_dol = temporary;
			}
		}
		tmp = tmp->next;
	}
}

void	new_token_dollars(char *word, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (shell->is_dol && is_whitespace(word[i]) && ft_isalnum(word[i]))
		{
			ft_lstadd_back_dol(&shell->dol,
				ft_lstnew_dol(ft_strndup(&word[j], i - j)));
			j = i;
			shell->is_dol = 0;
		}
		if (word[i] == '$' && i != 0)
		{
			shell->is_dol = 1;
			ft_lstadd_back_dol(&shell->dol,
				ft_lstnew_dol(ft_strndup(&word[j], i - j)));
			j = i;
		}
		i++;
	}
	ft_lstadd_back_dol(&shell->dol, ft_lstnew_dol(ft_strndup(&word[j], i - j)));
	shell->is_dol = 0;
}

int	parsing_dollars(t_shell *shell)
{
	t_token_list	*tmp;

	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == TYPE_HEREDOC && tmp->next->type == TYPE_WORD)
		{
			tmp->next->type = TYPE_SIMPLE_QUOTE;
		}
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
	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == TYPE_SIMPLE_QUOTE)
		{
			tmp->type = TYPE_WORD;
		}
		tmp = tmp->next;
	}
	return (0);
}
