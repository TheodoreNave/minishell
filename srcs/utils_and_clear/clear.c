/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:45:37 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/18 18:46:49 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_lst(t_shell *shell)
{
	if (shell->action)
		ft_lstclear_action(&shell->action);
	if (shell->dol)
		ft_lstclear_dol(&shell->dol);
	if (shell->token)
		ft_lstclear_shell(&shell->token);
	return ;
}

void	clear(t_shell *shell)
{
	clear_lst(shell);
	if (shell->new_env_tab)
	{
		free_split(shell->new_env_tab);
		shell->new_env_tab = NULL;
	}
	if (shell->opt2)
	{
		free_split(shell->opt2);
		shell->opt2 = NULL;
	}
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
	return ;
}

void	clear_end(t_shell *shell)
{
	clear(shell);
	if (shell->environ)
		ft_lstclear_env(&shell->environ);
	if (shell->home)
	{
		free(shell->home);
		shell->home = NULL;
	}
	ft_close_fd(shell);
	return ;
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pb;

	pb = b;
	while (len > 0)
	{
		*pb = c;
		pb++;
		len--;
	}
	return (b);
}

int	ft_count_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
