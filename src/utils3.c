/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:03:36 by jquil             #+#    #+#             */
/*   Updated: 2023/10/25 15:09:05 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == '=' || s2[i] == '=')
		return (0);
	return (s1[i] - s2[i]);
}

char	*get_home_path(char **env)
{
	int		i;
	int		n;
	char	*path;

	i = 0;
	while (env[i] && ft_envstrcmp(env[i], "HOME"))
		i++;
	if (!env[i])
		return (NULL);
	n = 0;
	while (env[i][n + 5])
		n++;
	path = malloc(sizeof(char) * (n + 1));
	if (!path)
		return (perror("malloc"), NULL);
	n = 0;
	while (env[i][n + 5])
	{
		path[n] = env[i][n + 5];
		n++;
	}
	path[n] = '\0';
	return (path);
}

char	**init_sep(void)
{
	char	**sep;

	sep = malloc(sizeof(char *) * 6);
	if (!sep)
		return (perror("malloc"), NULL);
	sep[0] = ft_strdup("|");
	sep[1] = ft_strdup(">");
	sep[2] = ft_strdup(">>");
	sep[3] = ft_strdup("<");
	sep[4] = ft_strdup("<<");
	sep[5] = NULL;
	return (sep);
}

char	*get_full_cmd(struct dirent *dir, char *tabi, char **tab)
{
	char	*val;

	val = ft_strdup(tabi);
	power_free(tab);
	return (str_add(
			str_add(val, "/", 1, 0), dir->d_name, 1, 0));
}

char	**get_path_tab(char **env)
{
	int		i;
	char	*val;
	char	**tab;

	i = 0;
	while (env[i] && ft_envstrcmp(env[i], "PATH="))
		i++;
	if (!env[i])
		return (NULL);
	val = get_value(env[i]);
	tab = ft_split(val, ':');
	free(val);
	return (tab);
}
