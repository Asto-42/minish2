/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/31 12:02:49 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extension_of_the_territory_2(t_shell *s, char *st,
	char *tmp, int exp)
{
	int	x;

	x = -1;
	while (s->env[++x])
	{
		if (ft_strlen(tmp) && ft_strenvcmp(tmp, s->env[x]))
		{
			st = ft_str_eg_cpy(s->env[x], st);
			return (st);
		}
	}
	if (!s->env[x])
		return (free(st), ft_strdup(""));
	if (s->env[x])
		st = ft_str_without_exp(st, exp);
	return (remove_quote(st));
}

char	*init_tmp_expand(char *str, int *x)
{
	char	*tmp;

	if (str[0] == 39 || str[0] == 34)
	{
		tmp = ft_calloc((ft_strlen(str)) + 1, sizeof (char));
		++x[0];
	}
	else if (str[0] == 91 && str[1] == 36 && str[ft_strlen(str)] == 93)
		tmp = ft_calloc((ft_strlen(str) - 3), sizeof(char));
	else
		tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*if_suite_in_expand(char *str, int x)
{
	char	*tmp;
	int		y;

	y = 0;
	if (!str)
		return (NULL);
	tmp = ft_calloc(ft_strlen(str + x) + 1, sizeof(char));
	while (str[x])
	{
		tmp[y] = str[x];
		x++;
		y++;
	}
	tmp[y] = '\0';
	tmp = remove_quote(tmp);
	return (tmp);
}

char	*assemble(char *str, char *tmp, char *dodge)
{
	char	*res;
	int		x;
	int		y;

	x = -1;
	y = -1;
	if (!tmp)
		return (str);
	res = ft_calloc (ft_strlen(str) + 1 + ft_strlen(tmp), sizeof(char));
	while (str[++x] && str[x + 1] == dodge[x])
		;
	while (str[++x] && str[x] == tmp[++y])
		;
	y = -1;
	while (str[++x])
		res[++y] = str[x];
	x = -1;
	while (tmp[++x])
		res[++y] = tmp[x];
	return (free(str), free(tmp), res);
}

char	*ft_extension_of_the_territory(t_shell *shell, char *s, int exp)
{
	int		x;
	int		y;
	char	*tmp;
	char	*tmp_2;

	x = -1;
	y = -1;
	if (!ft_strncmp(s, "$?", 20) && ft_need_expand(s) != -1)
		return (free(s), itoa(shell->errno));
	tmp = init_tmp_expand(s, &x);
	tmp_2 = NULL;
	if (!tmp)
		return (free(s), NULL);
	while (s[++x] && s[x] != 34 && s[x] != 39)
		if (s[x] != 39 && s[x] != 34 && s[x] != 36 && (s[x] < 91 || s[x] > 93))
			tmp[++y] = s[x];
	tmp[++y] = '\0';
	if (x + 1 < ft_strlen(s))
		tmp_2 = if_suite_in_expand(s, x + 1);
	s = ft_extension_of_the_territory_2(shell, s, tmp, exp);
	if (tmp_2 && s && ft_strlen(s) == 0 && ft_strlen(tmp_2) > 0)
		return (free(s), free(tmp), tmp_2);
	if (x + 1 < ft_strlen(s))
		s = assemble(s, tmp_2, tmp);
	return (free(tmp), s);
}
