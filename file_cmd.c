/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:24:23 by tnave             #+#    #+#             */
/*   Updated: 2021/12/02 17:59:34 by tnave            ###   ########.fr       */
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
	tpmp->opt = malloc(sizeof(size + 1));
	if (!tpmp->opt)
		return ;
	while (i < size)
	{
		tpmp->opt[i] = ft_strdup(tmp->word);
		i++;
		tmp = tmp->next;
	}
	tpmp->opt[i] = NULL;
}

int		fill_cmd(t_shell *shell)
{
	(void)shell;
	t_token_list *tmp;
	t_cmd_list *tpmp;

	tmp = shell->token;
	tpmp = malloc(sizeof(t_cmd_list));
	if (!tpmp)
		return (0);
	// while (tmp)
	// {
						printf("entre\n");
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
					// < fichier      ls -la -l
					if (tmp->type == TYPE_WORD)							// SI commande et/ou options
					{
						malloc_opt(tmp, tpmp);
						ft_lstadd_back_action(&shell->action, tpmp);
					}
					printf("tmp->ASDKJKLASJDLJASL = %d\n", tmp->type);
					printf("tmp->LOL = %s\n", tmp->word);
				}
				else
				{
					tpmp->type_end = TYPE_END;
					ft_lstadd_back_action(&shell->action, tpmp);
				}
			}
		}
		print_new_lst(shell->action);
	// 	tmp = tmp->next;
	// }

	return (0);
}