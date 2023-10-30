/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:00:58 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 12:37:43 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_str_env(char *env)
{
	int		x;
	char	*tmp;

	x = -1;
	while (env[++x] && env[x] != '=')
		;
	tmp = malloc ((x + 1) * sizeof(char));
	x = -1;
	while (env[++x] && env[x] != '=')
		tmp[x] = env[x];
	tmp[x] = '\0';
	return (tmp);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

int	check_end(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
	{
		i++;
		if (!str[i])
			return (0);
	}
	return (1);
}

char	*cpy(char *str, char *new)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	while (str[i] && check_end(str + i))
	{
		new[n] = str[i];
		i++;
		n++;
	}
	new[n] = '\0';
	free(str);
	return (new);
}

char	*ft_epurstr(char *str)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	len = ft_strlen(str) - i;
	while (str[i])
		i++;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i--;
		len--;
	}
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (perror("malloc"), NULL);
	return (cpy(str, new));
}
