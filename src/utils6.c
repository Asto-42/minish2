/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:38:50 by jquil             #+#    #+#             */
/*   Updated: 2023/10/30 12:41:02 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	count_word_2(char *arg, int x, int nb)
{
	if (arg[x] == 34)
	{
		while (arg[++x] != 34)
			;
	}
	if (arg[x] == 39)
	{
		while (arg[++x] != 39)
			;
	}
	if (arg[x] == 124)
		nb++;
	if (arg[x] != 124 && arg[x] != 9 && arg[x] != 32)
	{
		while (arg[x] && (arg[x] != 124 && arg[x] != 9 && arg[x] != 32))
			x++;
		if (!arg[x])
			return (nb);
	}
	return (nb);
}

int	count_word(char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = 1;
	while (arg[++x])
	{
		count_word_2(arg, x, nb);
	}
	return (nb);
}
