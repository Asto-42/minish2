/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:59:29 by jquil             #+#    #+#             */
/*   Updated: 2023/10/27 16:59:17 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote_2(char *str, char *new, int nb, int type)
{
	if (nb != 0)
	{
		new = remove_quote_3(str, nb, type);
		return (free(str), new);
	}
	else
		return (str);
}

// bool	need_remove_quote(char *str, char *new)
// {
// 	int	type;
// 	int	x;
// 	int	tmp;
// 	int	quote;

// 	x = -1;
// 	quote = 0;
// 	type = new[0];
// 	while (str[++x])
// 	{
// 		if (str[x] == type)
// 		{
// 			tmp = x;
// 			while (x >= 0)
// 			{
// 				if (str[x] == 39 || str[x] == 34)
// 					quote++;
// 				x--;
// 			}
// 			x = tmp + 1;
// 			while (str[x] && str[x] != str[tmp])
// 				x++;
// 			while (str[x])
// 			{
// 				if (str[x] == 39 || str[x] == 34)
// 					quote++;
// 				x++;
// 			}
// 		}
// 	}
// 	printf("quote = %i\n", quote);
// 	if (quote >= 2)
// 		return (0);
// 	else
// 		return (1);
// }

bool	need_remove_quote_again(char *new/*char *str*/)
{
	int	x;
	int	type;

	x = -1;
	// if (need_remove_quote(str, new) == 0)
	// 	return (0);
	while (new[++x])
	{
		if (new[x] == 34 || new[x] == 39)
		{
			type = new[x];
			x++;
			while (new[x + 1])
			{
				if (new[x] == type || new[x + 1] == type)
					return (1);
				++x;
			}
		}
	}
	return (0);
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
	if (need_remove_quote_again(new) == 1)
		new = remove_quote(new);
	return (new);
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
