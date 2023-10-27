/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:12:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/26 16:56:38 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *str)
{
	int		i;
	int		len;
	char	*new;
	int		n;

	i = 0;
	len = -1;
	while (str[i] && str[i] != '=')
		i++;
	while (str[i + 1 + ++len])
		;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (perror("malloc"), NULL);
	n = 0;
	while (str[++i])
	{
		new[n] = str[i];
		n++;
	}
	new[n] = '\0';
	return (new);
}

char	**copy_env(char **env)
{
	int		i;
	int		n;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * (tab_len(env) + 1));
	if (!new)
		return (perror("malloc"), NULL);
	while (env[++i] != NULL)
	{
		n = -1;
		new[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!new[i])
			return (perror("malloc"), NULL);
		while (env[i][++n])
			new[i][n] = env[i][n];
		new[i][n] = '\0';
	}
	new[i] = NULL;
	return (new);
}

void	init_env_2(t_shell *shell, char *shlvl, char *ito, char *str)
{
	update_env(str_add(shlvl, ito, 0, 0), shell, 1);
	free(shlvl);
	free(ito);
	free(str);
}

void	init_env(t_shell *shell, char **env)
{
	int		i;
	char	*str;
	char	*shlvl;
	char	*ito;

	i = 0;
	if (env[0])
	{
		shell->env = copy_env(env);
		if (!shell->env)
			return ;
		while (shell->env[i] && ft_envstrcmp(shell->env[i], "SHLVL="))
			i++;
		if (!shell->env[i])
		{
			ft_export(shell, "SHLVL=1");
			return ;
		}
		str = get_value(shell->env[i]);
		shlvl = ft_strdup("SHLVL=");
		ito = itoa(ft_atoi(str) + 1);
		init_env_2(shell, shlvl, str, ito);
	}
	else
		create_env(shell);
}
