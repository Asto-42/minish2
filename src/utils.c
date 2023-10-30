/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:51 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 12:37:36 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strenvcmp(char *tmp, char *env)
{
	char	*comp;

	comp = cut_str_env(env);
	if (ft_strncmp(comp, tmp, ft_strlen(comp)) == 0
		&& ft_strlen(comp) == ft_strlen(tmp))
		return (free(comp), 1);
	return (free(comp), 0);
}

void	power_free(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	mnsh_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i + 1] != ' '
		&& s2[i + 1] != ' ' && s1[i] == s2[i] && s2[i] != '\n')
		i++;
	return (s1[i] - s2[i]);
}

char	*get_args(char *line)
{
	char	*arg;
	int		i;

	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		arg = line + i + 1;
	else
		arg = NULL;
	return (arg);
}

char	*get_cmd_name(char *line)
{
	int		i;
	char	*cmd;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	cmd = malloc(sizeof(char) * i);
	if (!cmd)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (line[i] && line[i] == ' ')
	{
		cmd[i] = line[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}
