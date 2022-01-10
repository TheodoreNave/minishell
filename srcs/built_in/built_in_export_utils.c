/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:22:13 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/10 13:15:31 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**sort_tab_env(char **tab, int size)
{
	char	*tmp;
	int		i;
	int		is_ok;

	i = 0;
	is_ok = 0;
	while (tab && !is_ok)
	{
		is_ok = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				is_ok = 0;
			}
			i++;
		}
		size--;
	}
	return (tab);
}

int	ft_putstr_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			write(1, &str[i], 1);
			write(1, "\"", 1);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	write(1, "\"", 1);
	return (0);
}

int	print_new_sort_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')
		{
			if (tab[i][0] != '_' && tab[i][1] != '=')
			{
				write (1, "declare -x ", 12);
				ft_putstr_quotes(tab[i]);
				write(1, "\n", 1);
			}
		}
		i++;
	}
	return (0);
}

int	print_sort_env(t_env *env)
{
	char	**tab;
	int		size;
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	size = count_env_lst(env);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	while (tmp)
	{
		tab[i] = strdup(tmp->var_env);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	print_new_sort_tab(sort_tab_env(tab, size));
	free_split(tab);
	return (0);
}
