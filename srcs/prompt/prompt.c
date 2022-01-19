/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:23:56 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/17 15:41:41 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_ext_two(t_shell *shell)
{
	shell->pwd_temp = getcwd(shell->buff_pwd, sizeof(shell->buff_pwd));
	if (!shell->pwd_temp)
		free(shell->pwd_temp);
	return ;
}

void	prompt_ext_five(t_shell *shell)
{
	if (shell->environ)
		ft_lstclear_env(&shell->environ);
	write(1, "exit\n", 5);
	clear(shell);
	exit(0);
}

char	*prompt_ext_three(t_shell *shell, char *buff)
{
	char	*join_temp;

	join_temp = ft_strjoin(shell->pwd_temp, " $> ");
	buff = readline(join_temp);
	free(join_temp);
	shell->on = 0;
	return (buff);
}

char	*prompt_ext_four(t_shell *shell, char *buff)
{
	char	*temp;
	char	*join_temp;

	temp = getcwd(shell->buff_pwd, sizeof(shell->buff_pwd));
	if (!temp)
		free(temp);
	join_temp = ft_strjoin(temp, " $> ");
	buff = readline(join_temp);
	free(join_temp);
	return (buff);
}

char	*prompt(t_shell *shell, char *buff)
{
	if (shell->prompt)
		return (prompt_ext_one(shell, buff));
	if (buff)
		free_buff(buff);
	if (!shell->on)
		prompt_ext_two(shell);
	if (shell->on)
		buff = prompt_ext_three(shell, buff);
	else
		buff = prompt_ext_four(shell, buff);
	if (!buff)
		prompt_ext_five(shell);
	shell->on = 0;
	return (buff);
}
