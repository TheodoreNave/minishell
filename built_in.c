/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:44:39 by tnave             #+#    #+#             */
/*   Updated: 2021/12/08 18:51:39 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <linux/limits.h>

int		built_in_cd(t_shell *shell, char *path)
{
	if (chdir(path) == -1)
		ft_error_two(path, shell, 3);
	parse_pwd_two(shell);
		
	
	return (0);
}

int		built_in_pwd(t_shell *shell)
{
	char	current[PATH_MAX];

	if (getcwd(current, sizeof(current)))
		printf("%s\n", current);
	else
		ft_error_two("getcurrent()", shell, 1);
	return (0);
}

// int		built_in_env(t_env *environ)
// {
// 	int i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (*env[i])
// 			printf("%s\n", env[i]);
// 		i++;
// 	}
// 	return (0);
// }

int	built_in_unset(t_shell *shell, char **opt)
{
	t_env *tmp;

	tmp = shell->environ;

	int i;

	i = 0;
	while (tmp)
	{	
		if (ft_strncmp(tmp->var_env, opt[1], ft_strlen(opt[1])) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = strdup("");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

// int	built_in_exit(t_shell *shell)
// {
// 	(void)shell;
// 	//free ALL
// 	printf("exit\n");
// 	exit(0);
// }



int	is_built_in(char *cmd)
{
	// printf("cmd = [%s]\n", cmd);
	// printf("**********************\n");
	if (!strcmp(cmd, "cd"))
	{
		printf("cd est bon\n");
		return (1);
	}
	else if (!strcmp(cmd, "pwd"))
		return (1);
	else if (!strncmp(cmd, "env", 3))
		return (1);
	else if (!strncmp(cmd, "export", 6))
		return (1);
	// else if (!strncmp(cmd, "unset", 5))
	// 	return (1);
	// else if (!strncmp(cmd, "exit", 4))
	// 	return (1);
	// else if (!strncmp(cmd, "echo", 4))
	// 	return (1);
	else
		return (0);
}

int 	not_valid_export(char c)
{
	if (!((c >= 97 && c <= 122) || (c >= 65 && c <= 90)))
		return (0);
	return (1);
}


//a 97 to z 122 A 65 to Z 90
int 	built_in_export(char **opt, t_env *environ, t_shell *shell)
{
	int i;
	int j;

	i = 1;
	j = 0;
 
	while (opt[i])
	{
		if (!not_valid_export(opt[i][j]))
		{
			ft_error_two(opt[i], shell, 4);
			return (1);
		}
		while (opt[i][j])
		{
			if (opt[i][j] == '=')
			{
				if (opt[i][j + 1] != '\0' && opt[i][j + 1] != '=')
				{
					ft_lstadd_back_env(&environ, ft_lstnew_env(opt[i]));
					return (0);
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		built_in_check(char **env, char **built_in, t_shell *shell)
{
	(void)env;
	// printf("built_in[0] = %s\n", built_in);
	if (!strcmp(built_in[0], "cd"))
	{
		if (!built_in[1])
		{
			if (chdir(getenv("HOME")) == -1)
				ft_error_two("chdir()", shell, 1);
			parse_pwd_two(shell);
		}
		else
			built_in_cd(shell, built_in[1]);
	}
	else if (!strcmp(built_in[0], "pwd"))
		built_in_pwd(shell);
	else if (!strcmp(built_in[0], "env"))
		print_env_lst(shell->environ);
	else if (!strncmp(built_in[0], "unset", 5))
		built_in_unset(shell, built_in);
	else if (!strncmp(built_in[0], "export", 6))
		built_in_export(built_in, shell->environ, shell);
	// else if (strncmp(built_in[0], "exit", 4))
	// 	built_in_exit(shell);
	// if (strncmp(built_in[0], "echo", 4))
	// 	built_in_echo();
	return (1);
}