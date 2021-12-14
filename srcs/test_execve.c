/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:34:56 by tnave             #+#    #+#             */
/*   Updated: 2021/12/14 18:41:23 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_env_2(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			shell->parse_env = ft_split(is_slash(env[i]), ':');
			return (1);
		}
		i++;
	}
	return (0);
}



void		ft_check_access_mini(int i, t_shell *shell, char **tab, char **opt_test)
{
	(void)opt_test;
	while (shell->parse_env && shell->parse_env[i])
	{
		// shell->join = ft_strjoin_three(shell->parse_env[i], "/", shell->action->opt[0]);
		shell->join = ft_strjoin_three(shell->parse_env[i], "/", opt_test[0]);
		if (access(shell->join, F_OK) == 0)
		{
			printf("OK\n");
			// ft_lstadd_back(&utils->lst, ft_lstnew(shell->action->opt, ft_strdup(utils->join)));
			// execve(shell->join, shell->action->opt, tab);
			execve(shell->join, opt_test, tab);
		}
		i++;
	}
	// suite_pipex(utils, environ);
}


void 	parse_les_redirections(t_shell *shell)
{
	t_cmd_list *tmp;

	tmp = shell->action;
	while (tmp)
	{
		if (tmp->type_start == TYPE_REDIR_LEFT && tmp->fichier != NULL)
		{
			tmp->fd = open(tmp->fichier, O_RDONLY);
			printf("fd = %d\n", tmp->fd);
		}
		else if (tmp->type_start == TYPE_REDIR_RIGHT && tmp->fichier != NULL)
		{
			tmp->fd = open(tmp->fichier, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU, S_IRGRP, S_IROTH);
		}
		// else if (tmp->type_start == TYPE_REDIR && tmp->fichier != NULL)
		// {
		// 	tmp->fd = open(tmp->fichier, O_WRONLY | O_APPEND)
		// }
		// else if (tmp->type_start == TYPE_HEREDOC && tmp->fichier != NULL)
		// {

		// }

		tmp = tmp->next;
	}

}

char	**new_opt_action(t_shell *shell)
{
	int i;
	int j;
	t_cmd_list *tmp;
	char **temp;

	temp = NULL;
	i = 0;
	j = 0;
	tmp = shell->action;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->opt)
			i += ft_count_line(tmp->opt);
		if (tmp->fichier != NULL)
			i += 1;
		tmp = tmp->next;
	}
	tmp = shell->action;
	i = 0;
	temp = malloc(sizeof(char *) * i + 1);
	if (temp)
		return (NULL);
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->opt)
		{
			while (tmp->opt[j])
			{
				temp[i] = ft_strdup(tmp->opt[j]);
				j++;
				i++;
			}
		}
		if (tmp->fichier != NULL)
		{
			temp[i] = tmp->fichier;
			i++;
		}
		tmp = tmp->next;
		j = 0;
	}
	temp[i] = NULL;
	return (temp);
}

void	print_new_opt(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("new_opt = [%s]\n", tab[i]);
		i++;
	}
	return ;
}

int	test_execve(t_shell *shell)
{

	int size;
	char **tab;
	int i;
	t_env *tmp;

	tmp = shell->environ;
	i = 0;
	size = count_env_lst(tmp);
	tab = malloc(sizeof(char*) * (size + 1));
	if (!tab)
		return (0);
	while (tmp)
	{
		tab[i] = strdup(tmp->var_env);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;


	char *opt_test[4];

	opt_test[0] = "cat";
	opt_test[1] = "fichier";
	opt_test[2] = "-e";
	opt_test[3] = NULL;
	opt_test[4] = NULL;

	(void)opt_test;
	parse_les_redirections(shell);
	shell->opt2 = new_opt_action(shell);
	// if (!shell->opt2)
	// 	return (0);
	print_new_opt(shell->opt2);
	printf("test\n");
	if (parse_env_2(tab, shell))
	{
		ft_check_access_mini(0, shell, tab, opt_test);
		// ft_check_access_mini(0, shell, tab, shell->action->opt);
	}
	else
		printf("PATH NOT GOOD\n");

	return (0);
}