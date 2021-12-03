/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/12/03 19:16:53 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//before ac = 2 av[0] = ./pipex av[1] ls -la

int	parse_env_minishell(char **env, t_utils *utils)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			utils->parse_env = ft_split(is_slash(env[i]), ':');
			return (1);
		}
		i++;
	}
	return (0);
}

void	signals(int sig)
{
	if (sig == SIGQUIT)
	{
		return ;
	}
	if (sig == SIGINT)
	{
		sig = SIGCONT;
		write(1, "\n", 1);
		// write(1, "Minishell $> ", 13);
		return ;
	}
}

void	mem(t_utils *utils, t_shell *shell)
{
	ft_memset(utils, 0, sizeof(t_utils));
	ft_memset(shell, 0, sizeof(t_shell));
}

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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    char *buff;
    t_utils utils;
	t_shell shell;
	// t_token_list *tmp;
	// int i = 0;

	mem(&utils, &shell);
    parse_env_minishell(env, &utils);
		signal(SIGQUIT, signals);
		// signal(SIGINT, signals);
    while (1)
    {
		buff = readline("Minishell $> ");
		if (!parsing_shit(buff, &shell))
			return (0);
		// print_list_z(shell.token);
		if (parsing_shit_two(&shell))
			fill_cmd(&shell);
		// print_new_lst(shell.action);
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
	}
    write(1, "ciao\n", 5);
	return (0);
}
