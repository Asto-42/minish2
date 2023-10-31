/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:57:38 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 18:36:11 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *arg)
{
	int	i;
	int	equal;
	int	name;
	int	val;

	i = 0;
	equal = 0;
	name = 0;
	val = 0;
	while (arg[i])
	{
		if (!name && (!is_alphanum(arg[i])
				|| (arg[0] >= '0' && arg[0] <= '9')))
			return (printf("Export: Invalid format\n"), 1);
		if (arg[i] != ' ' && arg[i + 1] && arg[i + 1] == '=' && !equal)
			name = 1;
		if (arg[i] != ' ' && equal)
			val = 1;
		if (arg[i] == '=')
			equal++;
		i++;
	}
	if (equal != 1 || !name || !val)
		return (printf("Export: Invalid format\n"), 1);
	return (0);
}

int	check_exist(char *arg, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_envstrcmp(shell->env[i], arg))
			return (1);
		i++;
	}
	return (0);
}

void	add_env(char *arg, t_shell *shell)
{
	char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = ft_calloc((i + 2), sizeof(char *));
	if (!new_env)
	{
		perror("malloc");
		return ;
	}
	i = -1;
	while (shell->env[++i])
		new_env[i] = shell->env[i];
	new_env[i] = ft_strcpy(arg, new_env[i]);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return ;
}

void	update_env(char *arg, t_shell *shell, int fr_arg)
{
	int	i;

	i = 0;
	while (shell->env[i] && ft_envstrcmp(arg, shell->env[i]))
		i++;
	if (shell->env[i])
		free(shell->env[i]);
	shell->env[i] = ft_strdup(arg);
	if (fr_arg)
		free(arg);
	return ;
}

int	ft_export(t_shell *shell, char *arg)
{
	char	**args;

	args = NULL;
	if (!arg || !ft_strlen(arg) || check_arg(arg))
		return (1);
	else
	{
		args = ft_split(arg, 0);
		if (!check_exist(args[0], shell))
			add_env(args[0], shell);
		else
			update_env(args[0], shell, 0);
	}
	power_free(args);
	return (0);
}
