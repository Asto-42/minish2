/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   badline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:59:13 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/31 11:30:10 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(char *str)
{
	int	i;

	i = 0;
	if (!str[1])
		return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '>'
			&& str[i] != '<' && str[i] != '|')
			return (1);
		i++;
		if (str[i] && str[i] == '|')
			return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	}
	return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
}

int	check_redirects(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<'))
		i++;
	if ((str[0] == '>' && str[1] == '<')
		|| (str[0] == '<' && str[1] == '>'))
		return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	if (!str[i + 1])
		return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '>'
			&& str[i] != '<' && str[i] != '|')
			return (1);
		i++;
		if (str[i] && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	}
	return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
}

int	check_before(char *str, int idx)
{
	int	i;

	i = -1;
	while (str[++i] && i < idx)
	{
		if (str[i] != ' ' && str[i] != '|'
			&& str[i] != '>' && str[i] != '<')
			return (1);
	}
	return (printf("unexpected error near token \'%c\'\n", str[idx]), 0);
}

int	check_backslash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '\\')
			return (1);
	return (0);
}

int	badline(char *str, t_shell *shell)
{
	int	i;

	i = -1;
	if (!check_backslash(str))
		return (printf("unexpected error near token \'\\\'\n"), -42);
	while (str[++i])
	{
		if (str[i] == '|' && (!check_pipes(str + i) || !check_before(str, i)))
			return (-42);
		if ((str[i] == '>' || str[i] == '<')
			&& !check_redirects(str + i))
			return (-42);
		if (ft_strlen(str) == 1 && str[0] == '.')
			return (printf("unexpected error near token \'.\'\n"), -42);
		if (ft_strlen(str) == 2 && str[0] == '.' && str[1] == '.')
			return (printf("unexpected error near token \'.\'\n"), -42);
		if (str[i] == '>' || str[i] == '<')
			i++;
	}
	return (shell->errno);
}
