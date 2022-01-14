/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:19:43 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/14 18:29:55 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_value(t_shell *shell, t_cmd_list *tmp)
{
	if (shell->opt2)
	{
		free_split(shell->opt2);
		shell->opt2 = NULL;
	}
	shell->opt2 = new_opt_action(tmp);
	if (!shell->opt2)
		return ;
	parse_les_redirections(tmp, shell);
	if (shell->parse_env)
	{
		free_split(shell->parse_env);
		shell->parse_env = NULL;
	}
	if (shell->join)
	{
		free(shell->join);
		shell->join = NULL;
	}
	parse_env_2(shell);
}

void	reset_value(t_shell *shell)
{
	if (shell->join)
	{
		free(shell->join);
		shell->join = NULL;
	}
	if (shell->opt2)
	{
		free_split(shell->opt2);
		shell->opt2 = NULL;
	}
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->fd_temp = -1;
	if (shell->parse_env)
	{
		free_split(shell->parse_env);
		shell->parse_env = NULL;
	}
	if (shell->tmp_file)
	{
		unlink(shell->tmp_file);
		free(shell->tmp_file);
		shell->tmp_file = NULL;
	}
	return ;
}

char	**new_opt_action_ext(char **temp, t_cmd_list *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
		tmp = tmp->next;
		j = 0;
	}
	temp[i] = NULL;
	return (temp);
}

char	**new_opt_action(t_cmd_list *action)
{
	t_cmd_list	*tmp;
	int			i;
	int			j;
	char		**temp;

	i = 0;
	j = 0;
	tmp = action;
	temp = NULL;
	while (tmp && tmp->type_start != TYPE_PIPE)
	{
		if (tmp->opt)
			i += ft_count_line(tmp->opt);
		if (tmp->fichier != NULL)
			i += 1;
		tmp = tmp->next;
	}
	tmp = action;
	temp = malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (NULL);
	return (new_opt_action_ext(temp, tmp));
}
