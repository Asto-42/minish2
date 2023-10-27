/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:47:56 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/26 14:11:26 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strcpy(char *src, char *dest)
{
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (perror("malloc"), NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*copy_tab(char **tab, char *line)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	n = -1;
	while (tab[++n])
	{
		j = -1;
		while (tab[n][++j])
		{
			line[i] = tab[n][j];
			i++;
		}
	}
	line[i] = '\0';
	power_free(tab);
	return (line);
}

char	*ft_tab_to_str(char **tab)
{
	int		len;
	int		i;
	int		n;
	char	*line;

	len = 0;
	n = -1;
	while (tab[++n])
	{
		i = -1;
		while (tab[n][++i])
			len++;
		len++;
	}
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (perror("malloc"), NULL);
	return (copy_tab(tab, line));
}

char	**add_line(char **tab, char *line)
{
	char	**new;
	int		i;

	i = -1;
	while (tab[++i])
		;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (perror("malloc"), NULL);
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strcpy(tab[i], new[i]);
		i++;
	}
	new[i] = ft_strcpy(line, new[i]);
	new[i + 1] = NULL;
	power_free(tab);
	return (new);
}

char	*get_heredoc(char *delimiter)
{
	char	**heredoc;
	char	*line;

	line = NULL;
	heredoc = malloc(sizeof(char *));
	heredoc[0] = NULL;
	if (!heredoc)
		return (perror("malloc"), NULL);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO, delimiter);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		heredoc = add_line(heredoc, line);
		free(line);
		if (heredoc == NULL)
			return (NULL);
	}
	free(line);
	return (ft_tab_to_str(heredoc));
}
