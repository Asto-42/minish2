/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:15:13 by jquil             #+#    #+#             */
/*   Updated: 2023/10/31 11:45:22 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_start(char *str, int x)
{
	int	start;

	start = x;
	while (str[x])
	{
		if (str[x] == 124)
		{
			start = x;
			return (start + 1);
		}
		if (str[x] != 124 && str[x] != 32 && str[x] != 9)
		{
			start = x;
			return (start);
		}
		x++;
	}
	return (0);
}

char	**resplit_tab_2(char **tab, char **new, int i, int size)
{
	int	n;

	n = 0;
	i = -1;
	size = 0;
	while (tab[++i])
	{
		if (tab[i + 1] == NULL || ft_strncmp(tab[i + 1], "|", 1) == 0)
		{
			if (n > 0)
				size--;
			new[n] = copy_line(tab, i, size);
			n++;
			size = -1;
		}
		size++;
	}
	new[n] = NULL;
	if (tab)
		power_free(tab);
	return (new);
}

char	**resplit_tab(char **tab)
{
	char	**new;
	int		i;
	int		size;

	i = -1;
	size = 1;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], "|", 1) == 0)
			size++;
	}
	new = ft_calloc((size + 1), sizeof(char *));
	if (!new)
		return (perror("malloc"), NULL);
	new = resplit_tab_2(tab, new, i, size);
	return (new);
}

char	*epur_str_expand(char *str)
{
	int		x;
	int		y;
	char	*new;

	x = -1;
	y = -1;
	new = ft_calloc((ft_strlen(str)) + 1, sizeof(char));
	if (str[++x] == '$')
	{
		if (str[++x] == 34 || str[x] == 39)
		{
			while (str[++x] && str[x] != 34 && str[x] != 39)
				new[++y] = str[x];
			if (str[x] == 34 || str[x] == 39)
			{
				while (str[++x] && str[x] != 34 && str[x] != 39)
					new[++y] = str[x];
			}
		}
	}
	return (free(str), new);
}

char	**ft_split_str(t_shell *shell, char *str, char **tab)
{
	int		z;

	z = -1;
	tab = ft_split(str, ' ');
	if (!tab)
		return (NULL);
	while (tab[++z])
	{
		if (ft_need_expand(tab[z]) > -1
			&& expand_not_quoted(tab[z], ft_need_expand(tab[z])) == 1)
		{
			tab[z] = ft_extension_of_the_territory(shell, tab[z],
					ft_need_expand(tab[z]) + 1);
		}
		else if (ft_need_expand(tab[z]) == -2)
			tab[z] = epur_str_expand(tab[z]);
		else
			tab[z] = remove_quote(tab[z]);
	}
	tab[z] = NULL;
	tab = resplit_tab(tab);
	return (tab);
}
