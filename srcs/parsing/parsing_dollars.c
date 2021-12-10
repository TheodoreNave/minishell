/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:20:59 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/10 19:09:28 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\0' || str[i] == ' ' || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strndup(char *str, int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (!(dest))
		return (NULL);
	while (str[i] && i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void convert_dollars(char *word, t_shell *shell)
{
	t_env *tmp;

	tmp = shell->environ;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, word, ft_strlen_space(word)) == 0)
		{
			ft_lstadd_back_dol(&shell->dol, ft_lstnew_dol(ft_strndup(&tmp->var_env[ft_strlen_egal(tmp->var_env) + 1], ft_strlen_space(word))));
		}
		tmp = tmp->next;
	}
	return ;
}

int	check_dollars(t_shell *shell, char *word)
{
	(void)shell;
	int i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			convert_dollars(&word[i + 1], shell);
		i++;
	}
	return (0);
}

char 	*new_token(char *word, t_dol *dol)
{
	char *new;
	int i;

	i = 0;
	while ()
}

int parsing_dollars(t_shell *shell)
{
	char *token_temp;
	t_token_list *tmp;
	int i;

	tmp = shell->token;
	i = 0;
	while (tmp)
	{
		if (tmp->type == TYPE_WORD)
		{
			if (check_dollars(shell, tmp->word) == 1)
			{
				token_temp = tmp->word;
				tmp->word = new_token(tmp->word, shell->dol);
				free(token_temp);
			}	
		}
		tmp = tmp->next;
	}
	print_list_dol(shell->dol);
	return (0);
}

// "salut [$theos] $TIM" if good keep and change else KO 