/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:55:32 by tnave             #+#    #+#             */
/*   Updated: 2021/12/08 18:06:11 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	mem(t_utils *utils, t_shell *shell)
{
	ft_memset(utils, 0, sizeof(t_utils));
	ft_memset(shell, 0, sizeof(t_shell));
}


char	*prompt(t_shell *shell, char *buff)
{
	char *temp;
	char *join_temp;
	
	if (shell->on == 0)
	{// free shell->pwd_temp
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
		join_temp = ft_strjoin(temp , " $> ");
		buff = readline(join_temp);
		free(join_temp);
	}
	if (!buff)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	return (buff);
}

int		stock_env(char **env, t_shell *shell)
{
	(void)shell;
	int i;
	int j;

	i = 0;
	j = 1;
	while (env[i])
	{
		ft_lstadd_back_env(&shell->environ, ft_lstnew_env(env[i]));
		i++;
	}
	return (0);
}

int 	parse_pwd_two(t_shell *shell)
{
	int i;
	t_env *tmp;
	t_env *tempo;
	char *pwd_temp;
	
	pwd_temp = NULL;
	tmp = shell->environ;
	tempo = shell->environ;
	i = 0;
	while (tempo)
	{
		if (ft_strncmp(tempo->var_env, "PWD=", 4) == 0)
		{					
			pwd_temp = ft_strjoin("OLD", tempo->var_env);
		}
		tempo = tempo->next;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, "OLDPWD=", 7) == 0)
		{
			
			free(tmp->var_env);
			tmp->var_env = ft_strdup(pwd_temp);
		}
		if (ft_strncmp(tmp->var_env, "PWD=", 4) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("PWD=", getcwd(shell->buff_pwd, sizeof(shell->buff_pwd)));
		}
		i++;
		tmp = tmp->next;
	}
	free(pwd_temp);
	return (0);
}


int 	parse_pwd(t_shell *shell)
{
	int i;
	t_env *tmp;

	tmp = shell->environ;
	i = 0;
	
	while (tmp)
	{
		if (ft_strncmp(tmp->var_env, "PWD=", 4) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("PWD=", getcwd(shell->buff_pwd, sizeof(shell->buff_pwd)));
		}
		if (ft_strncmp(tmp->var_env, "OLDPWD=", 7) == 0)
		{
			free(tmp->var_env);
			tmp->var_env = ft_strjoin("OLDPWD=", getcwd(shell->buff_pwd, sizeof(shell->buff_pwd)));
		}
		tmp = tmp->next;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

    t_utils utils;
	t_shell shell;

	mem(&utils, &shell);
	if (chdir(getenv("HOME")) == -1)
		ft_error_two("chdir()", &shell, 1);
	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals);
	stock_env(env, &shell);
	parse_pwd(&shell);
	// print_env_lst(shell.environ);
    while (1)
    {
		rl_line_buffer = prompt(&shell, rl_line_buffer);
		add_history(rl_line_buffer);
		if (!parsing_shit(rl_line_buffer, &shell))
			return (0);
		if (parsing_shit_two(&shell))
			fill_cmd(&shell);

		parse_env_minishell(env, &utils);
		
		if (shell.action)
		{
			if (is_built_in(shell.action->opt[0]))
			{
				// printf("cmd is ok\n");
				built_in_check(env, shell.action->opt, &shell);
			}
			else
			{
					// printf("pas la bonne commande\n");
			}
		}
		// free(rl_line_buffer); //free dans une fonction pour la norme
		ft_lstclear_shell(&shell.token);
		ft_lstclear_action(&shell.action);
		// print_new_lst(shell.action);
		// print_list_z(shell.token);
	}
    write(1, "ciao\n", 5);
	return (0);
}
