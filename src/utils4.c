/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:59:29 by jquil             #+#    #+#             */
/*   Updated: 2023/10/30 14:57:35 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote_2(char *str, char *new, int nb, int type)
{
	if (nb != 0)
	{
		new = remove_quote_3(str, nb, type);
		return (new);
	}
	else
		return (str);
}

char	*remove_quote_from_new(char *new, char c)
{
	int	x;
	int	nb;
	int	tmp;

	x = -1;
	nb = 0;
	while (new[++x] && nb < 2)
	{
		if (new[x] == c)
		{
			tmp = x;
			while (new[x])
			{
				new[x] = new[x + 1];
				x++;
			}
			x = tmp;
			nb++;
		}
	}
	new[x + 1] = '\0';
	return (new);
}

char	*need_remove_quote_again_2(char *new, char *str, int *tab, int size)
{
	int	x;

	x = 0;
	while (x + 4 <= size + 1)
	{
		if (str[tab[x]] == str[tab[x + 1]]
			&& str[tab[x + 2]] == str[tab[x + 3]])
			new = remove_quote_from_new(new, str[tab[x + 2]]);
		x += 4;
	}
	if (strncmp(str, new, ft_strlen(str)))
		free(str);
	return (new);
}

char	*need_remove_quote_again(char *new, char *str)
{
	int	x;
	int	quote;
	int	*tab;
	int	y;

	x = -1;
	y = -1;
	quote = 0;
	while (str[++x])
	{
		if (str[x] == 34 || str[x] == 39)
			quote++;
	}
	if (quote % 2 != 0)
		return (free(str), new);
	tab = malloc (quote * sizeof(int));
	x = -1;
	while (str[++x])
	{
		if (str[x] == 34 || str[x] == 39)
			tab[++y] = x;
	}
	new = need_remove_quote_again_2(new, str, tab, y);
	return (free(tab), new);
}

char	*remove_quote(char *str)
{
	int		x;
	int		nb;
	char	*new;
	int		type;

	nb = 0;
	x = -1;
	new = NULL;
	type = 0;
	while (str[++x])
	{
		if (str[x] == 39 || str[x] == 34 || str[x] == 92)
		{
			++nb;
			type = str[x];
			while (str[++x] && str[x] != type)
				;
			++nb;
			break ;
		}
	}
	new = remove_quote_2(str, new, nb, type);
	new = need_remove_quote_again(new, str);
	return (new);
}
