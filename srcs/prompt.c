/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:23:56 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/10 20:11:12 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt(t_shell *shell, char *buff)
{
	char	*temp;
	char	*join_temp;

	if (shell->prompt)
	{
		buff = readline(">\n");
		shell->prompt = 0;
		return (buff);
	}
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	if (!shell->on)
	{
		shell->pwd_temp = getcwd(shell->buff_pwd, sizeof(shell->buff_pwd));
		if (!shell->pwd_temp)
			free(shell->pwd_temp);
	}
	if (shell->on)
	{
		join_temp = ft_strjoin(shell->pwd_temp, " $> ");
		buff = readline(join_temp);
		free(join_temp);
		shell->on = 0;
	}
	else
	{
		temp = getcwd(shell->buff_pwd, sizeof(shell->buff_pwd));
		if (!temp)
			free(temp);
		join_temp = ft_strjoin(temp, " $> ");
		buff = readline(join_temp);
		free(join_temp);
	}
	if (!buff)
	{
		if (shell->environ)
			ft_lstclear_env(&shell->environ);
		write(1, "exit\n", 5);
		exit(0);
	}
	shell->on = 0;
	return (buff);
}
