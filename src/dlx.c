/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:26:41 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 14:26:50 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*douillax(char *str)
{
	int	i;
	int	in_quote;

	i = -1;
	in_quote = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' && check_endz(str + i, '\''))
			|| (str[i] == '\"' && check_endz(str + i, '\"')))
			in_quote = 1;
		else if ((str[i] == '\'' || str[i] == '\"') && in_quote)
			in_quote = 0;
		if (str[i] == '>' && in_quote)
			str[i] = 1;
		if (str[i] == '<' && in_quote)
			str[i] = 2;
		if (str[i] == '|' && in_quote)
			str[i] = 3;
	}
	return (str);
}

char	*anti_douillax(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == 1)
			str[i] = '>';
		if (str[i] == 2)
			str[i] = '<';
		if (str[i] == 3)
			str[i] = '|';
	}
	return (str);
}