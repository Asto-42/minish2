/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:14:07 by jquil             #+#    #+#             */
/*   Updated: 2023/10/31 11:17:55 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*itoa_2(char *str, int nb, int len)
{
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str += len;
	*str = '\0';
	while (nb != 0)
	{
		*--str = '0' + (nb % 10);
		nb /= 10;
	}
	return (str);
}

char	*itoa(int nb)
{
	int		len;
	int		temp;
	char	*str;

	temp = nb / 10;
	len = 1;
	while (temp)
	{
		len++;
		temp /= 10;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (perror("malloc"), NULL);
	return (itoa_2(str, nb, len));
}

bool	ft_next_quote(char *arg, int type, int x)
{
	int	y;

	y = x;
	while (arg[++y])
	{
		if (arg[y] == type)
			return (1);
	}
	return (0);
}
