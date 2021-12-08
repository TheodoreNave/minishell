/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:45:28 by tnave             #+#    #+#             */
/*   Updated: 2021/12/08 19:00:05 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void 	print_list_z(t_token_list *token)
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

void	print_env_lst(t_env *env)
{
	t_env *tmp;
	int i = 0;

	tmp = env;
	while (tmp)
	{
		if (tmp->var_env[0] != '\0')
		{
			printf("------------------------------------\n");
			printf("env[%d] = [%s]\n", i, tmp->var_env);
		}
		i++;
		tmp = tmp->next;
	}
	printf("------------------------------------\n");
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
