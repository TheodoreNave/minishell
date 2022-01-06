/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:16:14 by tigerber          #+#    #+#             */
/*   Updated: 2022/01/06 14:55:18 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strcpy(char *buff, char *str)
{
	int i;

	i = 0;
	if ((!str[i]) || (!buff))
		return ;
	while(str[i])
	{
		buff[i] = str[i];
		i++;
	}
	return ;
}

void	ft_putstr_fderr(char *str, char *str2)
{
	char buff[2048];
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == 's')
		{
			ft_strcpy(&buff[j], str2);
			j += ft_strlen(str2);
			i++; 
		}
		else
			buff[j++] = str[i];
		i++;
	}
	write(STDERR_FILENO, buff, j);
	return ;
}

int	ft_error_two(char *str, t_shell *shell, int error)
{
	//printf les erreurs sur la sortie d'erreur STDERR
	if (error == 1)
	{	
		ft_putstr_fderr("bash: syntax error near unexpected token `%s'\n", str);
		shell->error_dol = 258;
	}
	if (error == 2)
	{
		ft_putstr_fderr(">\n", NULL);
	}
	if (error == 3)
	{
		ft_putstr_fderr("bash: cd: %s: No such file or directory\n", str);
		shell->error_dol = 1;
		shell->on = 1;
	}
	if (error == 4)
	{
		ft_putstr_fderr("bash: export: `%s': not a valid identifier\n", str);
		shell->error_dol = 1;
	}
	if (error == 5)
	{
		ft_putstr_fderr("bash: unset: `%s': not a valid identifier\n", str);
		shell->error_dol = 1;
	}
	if (error == 6)
	{
		ft_putstr_fderr("NO ENV FOUND SORRY NEED TO QUIT %s\n", str);
		// shell->error_dol = 127;
		exit(127);
	}
	if (error == 7)
	{
		ft_putstr_fderr("%s", str);
		shell->error_dol = 1;
	}
	return (0);
}

	// Script end by ctrl-D -> 130
	// Fatal error signal comme kill -9 $PPID -> 128 + n
	// Mauvaise utilisation de shell builtin -> 2

	// if prompt /dev/null -> Permission denied Error message 126


	// ft_lstclear_shell(&shell->token);
	// ft_lstclear_action(&shell->action);
	// strerror(errno) plus tard