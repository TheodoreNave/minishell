/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:45:28 by tnave             #+#    #+#             */
/*   Updated: 2021/12/16 19:01:32 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_new_opt(char **tab)
{
	int i;

	i = 0;
	printf("---------------------****----------------------\n");
	while (tab[i])
	{
		printf("new_opt = [%s]\n", tab[i]);
		i++;
	}
	printf("-----------------------------------------------\n");
	return ;
}

void 	print_token_list(t_token_list *token)
{
	t_token_list *tmp;

	tmp = token;

	while (tmp)
	{
		printf("========================\n");
		printf("prev = [%p]\n", tmp->prev);
		printf("temp = [%p]\n", tmp);
		printf("Token = [%s]\n", tmp->word);
		printf("type = [%d]\n", tmp->type);
		printf("next = [%p]\n", tmp->next);
		printf("========================\n");
		tmp = tmp->next;
	}

}

void 	print_list_dol(t_dol *token)
{
	t_dol *tmp;

	tmp = token;

	while (tmp)
	{
		printf("========================\n");
		printf("prev = [%p]\n", tmp->prev);
		printf("temp = [%p]\n", tmp);
		printf("word_dol = [%s]\n", tmp->word_dol);
		printf("next = [%p]\n", tmp->next);
		printf("========================\n");
		tmp = tmp->next;
	}
		printf("____________________________________________________\n");
}


void	print_env_lst(t_env *env, int indic)			// If option -> ft_error
{
	t_env *tmp;

	tmp = env;
	if (indic == 1)
	{
		while (tmp)
		{
			if (tmp->var_env[0] != '\0')
			{
				printf("%s\n", tmp->var_env);
			}
			tmp = tmp->next;
		}
	}
}

void 	print_new_lst(t_cmd_list *lst)
{
	t_cmd_list *tmp;
	tmp = lst;
	int j = 1;
	int i = 0;
	while (tmp)
	{
		printf("*--------------------------NEW-LST-[%d]---------------------*\n", j);
		printf("|	Adresse     = [%p]                                       \n", tmp);
		printf("|	Type start  = [%d]                                       \n", tmp->type_start);
		printf("|	Fichier     = [%s]                                       \n", tmp->fichier);
		printf("|		*----------------opt-------------*                   \n");
		if (tmp->opt)
		{
			while (tmp->opt[i])
			{
		printf("|		|	opt[%d] = [%s]                                   \n", i, tmp->opt[i]);
				i++;
			}
			i = 0;
		}
		printf("|		*----------------opt-------------*                   \n");
		printf("|	Type end    = [%d]                                       \n", tmp->type_end);
		printf("|	AdresseNext = [%p]                                       \n", tmp->next);
		printf("*-----------------------------------------------------------*\n");
		printf("\n");
		j++;
		tmp = tmp->next;
	}
}
