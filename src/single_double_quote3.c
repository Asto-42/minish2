/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:12:59 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/31 11:49:46 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_need_expand(char *str)
{
	int	x;

	x = -1;
	while (str[++x])
	{
		if (str[x] == '$' && /*str[x + 1]&&*/  str[x + 1] != 34 && str[x + 1] != 39)
			return (x);
		else if (str[x] == '$' && (str[x + 1] == 34 || str[x + 1] == 39))
			return (-2);
	}
	return (-1);
}

char	*ft_add_str(t_shell *shell, char *str, int start, int end)
{
	char	*dest;
	int		x;

	x = 0;
	dest = malloc ((end - start + 1) * sizeof(char));
	if (!dest)
		return (perror("malloc"), NULL);
	(void)shell;
	while (start < end)
	{
		if (str[start] != 34 && str[start] != 39)
		{
			dest[x] = str[start];
			x++;
		}
		start++;
	}
	dest[x] = '\0';
	return (dest);
}

int	calc_size(char **tab, int idx, int size)
{
	int	n_size;

	n_size = 0;
	while (size)
	{
		n_size += ft_strlen(tab[idx - size]) + 1;
		size--;
	}
	n_size += ft_strlen(tab[idx - size]);
	return (n_size);
}

char	*copy_line(char **tab, int idx, int size)
{
	char	*new;

	new = ft_calloc((calc_size(tab, idx, size) + 1), sizeof(char));
	if (!new)
		return (perror("malloc"), NULL);
	while (size)
	{
		new = str_add(new, tab[idx - size], 1, 0);
		new = str_add(new, " ", 1, 0);
		size--;
	}
	new = str_add(new, tab[idx], 1, 0);
	return (new);
}
