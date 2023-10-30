/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:15:05 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 14:31:16 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->builtins = malloc(sizeof(char *) * 8);
	if (!shell->builtins)
	{
		perror("malloc");
		exit(1);
	}
	init_signals();
	init_env(shell, env);
	getcwd(shell->ex_path, sizeof(shell->ex_path));
	shell->errno = 0;
	shell->builtins[0] = ft_strdup("echo");
	shell->builtins[1] = ft_strdup("cd");
	shell->builtins[2] = ft_strdup("pwd");
	shell->builtins[3] = ft_strdup("export");
	shell->builtins[4] = ft_strdup("unset");
	shell->builtins[5] = ft_strdup("env");
	shell->builtins[6] = ft_strdup("exit");
	shell->builtins[7] = NULL;
	shell->f_ptr[0] = ft_echo;
	shell->f_ptr[1] = ft_cd;
	shell->f_ptr[2] = ft_pwd;
	shell->f_ptr[3] = ft_export;
	shell->f_ptr[4] = ft_unset;
	shell->f_ptr[5] = ft_env;
	shell->f_ptr[6] = ft_exit;
}

char	*get_cwd(void)
{
	int		i;
	int		n;
	char	cwd[MAX_PATH_SIZE];
	char	*res;

	i = 0;
	n = 1;
	getcwd(cwd, sizeof(cwd));
	while (cwd[i])
		i++;
	while (cwd[i - n] != '/')
		n++;
	i -= n;
	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		return (perror("malloc"), NULL);
	n = 0;
	while (cwd[i + n + 1])
	{
		res[n] = cwd[i + n + 1];
		n++;
	}
	res[n] = '\0';
	return (res);
}

char	*init_builtins(char *cmd)
{
	char	**tab;
	char	**nr;
	char	*arg;
	int		i;

	if (!ft_strlen(cmd))
		return (cmd);
	tab = ft_split(cmd, ' ');
	if (!tab[1])
	{
		power_free(tab);
		return (NULL);
	}
	else
		nr = ignore_redirections(&tab[1], 0);
	i = -1;
	while (nr[++i])
		if (nr[i + 1])
			nr[i] = str_add(nr[i], " ", 1, 0);
	arg = ft_tab_to_str(nr);
	power_free(tab);
	return (arg);
}

void	patch(t_shell *shell, char *arg)
{
	free(arg);
	ft_exit(shell, itoa(shell->errno));
}

int	check_endz(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}
