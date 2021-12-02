/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:24:23 by tnave             #+#    #+#             */
/*   Updated: 2021/12/02 20:15:09 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// printf("OKAY\n");

void		malloc_opt(t_token_list *tmp, t_cmd_list *tpmp)
{
	int i;
	int size;

	i = 0;
	size = ft_lstsize_shell(tmp);
	tpmp->opt = malloc(sizeof(char *) * (size + 1));
	if (!tpmp->opt)
		return ;
	while (i < size)
	{
		tpmp->opt[i] = ft_strdup(tmp->word);
		printf("+++ allocating %p for %s\n", tpmp->opt[i], tmp->word);
		i++;
		tmp = tmp->next;
	}
	tpmp->opt[i] = NULL;
}

int		fill_cmd(t_shell *shell)
{
	t_token_list *tmp;

	tmp = shell->token;
	while (tmp)
	{
		printf("LAPS\n");
		t_cmd_list *tpmp;
		tpmp = malloc(sizeof(t_cmd_list));
		if (!tpmp)
			return (0);
		ft_memset(tpmp, 0, sizeof(t_cmd_list));
		if (tmp->type == TYPE_REDIR_LEFT || tmp->type == TYPE_REDIR_RIGHT)
		{
			tpmp->type_start = tmp->type;
			tmp = tmp->next;
			if (tmp)
			{
				tpmp->fichier = ft_strdup(tmp->word);
				tmp = tmp->next;
				if (tmp)
				{
					if (tmp->type == TYPE_WORD)							// SI commande et/ou options
						malloc_opt(tmp, tpmp);
					while (tmp != NULL && tmp->type == TYPE_WORD)
						tmp = tmp->next;
					if (tmp)
					{
						printf("TMP->TYPE = %d\n", tmp->type);
						printf("TMP->WORD = %s\n", tmp->word);
						tpmp->type_end = tmp->type;
						ft_lstadd_back_action(&shell->action, tpmp);
						tmp = tmp->prev;
					}
					else
					{
						tpmp->type_end = TYPE_END;
						ft_lstadd_back_action(&shell->action, tpmp);
						printf("OK\n");
						break ;
					}
				}
				else
				{
					tpmp->type_end = TYPE_END;
					ft_lstadd_back_action(&shell->action, tpmp);
				}
			}
		}
		tmp = tmp->next;
	}
	print_new_lst(shell->action);

	return (0);
}