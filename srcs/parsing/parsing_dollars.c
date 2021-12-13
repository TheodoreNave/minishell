/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:20:59 by tigerber          #+#    #+#             */
/*   Updated: 2021/12/13 18:06:41 by tnave            ###   ########.fr       */
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

char *convert_dollars(char *word, t_shell *shell)
{
	t_env *tmp;
	int size;
	char *join;

	tmp = shell->environ;
	size = ft_strlen_space(word);
	join = NULL;

	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, word, size) == 0)
		{
			if ((tmp->var_env[size] == '='))
				join = ft_strjoin(&tmp->var_env[size + 1], &word[size]);
			return (join);
		}
		tmp = tmp->next;
	}
	return (ft_strjoin("", &word[size]));
}

int	check_dollars(t_shell *shell, char *word)
{
	(void)shell;
	int i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_whitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r');
}

int		dollars_question(t_shell *shell)
{
	shell->dol->question_dol = 1;
	return (0);
}

void	recup_dollars(t_shell *shell)
{
	t_dol *tmp;
	char *temporary;

	temporary = NULL;
	tmp = shell->dol;
	while (tmp)
	{
		if (tmp->word_dol[0] == '$' && tmp->word_dol[1] == '?' && tmp->word_dol[2] == '\0')
		{
			dollars_question(shell);
		}
		if (tmp->word_dol[0] == '$' && (!is_whitespace(tmp->word_dol[1])) && tmp->word_dol[1] != '\0')
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

void 	new_token_dollars(char *word, t_shell *shell)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (shell->is_dol && is_whitespace(word[i]))
		{
			ft_lstadd_back_dol(&shell->dol, ft_lstnew_dol(ft_strndup(&word[j], i - j)));
			j = i;
			shell->is_dol = 0;
		}
		if (word[i] == '$' && i != 0)
		{
			shell->is_dol = 1;
			ft_lstadd_back_dol(&shell->dol, ft_lstnew_dol(ft_strndup(&word[j], i - j)));
			j = i;
		}
		i++;
	}
	ft_lstadd_back_dol(&shell->dol, ft_lstnew_dol(ft_strndup(&word[j], i - j)));
	shell->is_dol = 0;
}

char	*join_dollars(t_shell *shell)
{
	t_dol *tmp;
	char  *new_str;
	char  *temp;

	new_str = ft_strdup("");
	temp = NULL;
	tmp = shell->dol;
	// print_list_dol(shell->dol);
	while (tmp)
	{
		temp = new_str;
		new_str = ft_strjoin(new_str, tmp->word_dol);
		free(temp);
		tmp = tmp->next;
	}
	return (new_str);
}

int parsing_dollars(t_shell *shell)
{
	t_token_list *tmp;

	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == TYPE_WORD)
		{
			if (check_dollars(shell, tmp->word))
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
	// print_list_dol(shell->dol);
	// print_list_z(shell->token);
	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == TYPE_SIMPLE_QUOTE)
		{
			tmp->type = TYPE_WORD;
		}
		tmp = tmp->next;
	}
	// print_list_dol(shell->dol);
	// print_list_z(shell->token);

	return (0);
}
