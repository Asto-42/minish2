/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:02:39 by jquil             #+#    #+#             */
/*   Updated: 2023/10/30 12:33:23 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_without_exp_2(char *str, char *str2)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	if (ft_strncmp(str, "$", 2) == 0)
	{
		str2[0] = '$';
		str2[1] = '\0';
		return (str2);
	}
	while (str[++x])
	{
		if (str[x] && str[x] != '$' && str[x] != 34 && str[x] != 39)
			str2[++y] = str[x];
		if (str[x] == '$')
		{
			while (str[x] && str[x] != 32
				&& str[x] != 9 && str[x] != 34 && str[x] != 39)
				++x;
			x--;
		}
	}
	str2[++y] = '\0';
	return (str2);
}

char	*ft_str_without_exp(char *str, int exp)
{
	int		tmp;
	int		x;
	char	*str2;

	x = -1;
	while (str[++x] && str[x] != 32 && str[x] != 9)
		;
	tmp = exp;
	while (str[exp] && str[exp] >= 65 && str[exp] <= 90)
		--exp;
	str2 = malloc ((x + (tmp - exp) + 1) * sizeof(char));
	if (!str2)
		return (perror("malloc"), NULL);
	tmp++;
	str2 = ft_str_without_exp_2(str, str2);
	return (str2);
}

char	*init_cmd(char *cmd, char **env)
{
	char			**tab;
	int				i;
	DIR				*d;
	struct dirent	*dir;

	tab = get_path_tab(env);
	i = -1;
	while (tab && tab[++i])
	{
		d = opendir(tab[i]);
		if (d)
		{
			dir = readdir(d);
			while (dir != NULL)
			{
				if (ft_strncmp(cmd, dir->d_name,
						ft_strlen(cmd) + ft_strlen(dir->d_name)) == 0)
					return (get_full_cmd(dir, tab[i], tab));
				dir = readdir(d);
			}
		}
		closedir(d);
	}
	power_free(tab);
	return (NULL);
}

char	*get_cmd(char *line, char **env)
{
	char	*cmd;
	char	**tab;

	cmd = NULL;
	tab = ft_split(line, ' ');
	cmd = init_cmd(tab[0], env);
	if (!cmd)
		cmd = ft_strcpy(tab[0], cmd);
	if (tab)
		power_free(tab);
	return (cmd);
}

char	*remove_quote_3(char *str, int nb, int type)
{
	int		x;
	int		y;
	char	*new;

	y = -1;
	new = ft_calloc((ft_strlen(str) - nb + 2), sizeof (char));
	if (!new)
		return (NULL);
	x = -1;
	while (str[++x])
	{
		if (str[x] != type && str[x] != 92)
			new[++y] = str[x];
	}
	++y;
	new[y] = '\0';
	return (new);
}
