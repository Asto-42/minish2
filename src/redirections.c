/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:29:10 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/26 12:41:43 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_right(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

int	double_right(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

int	simple_left(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	return (fd);
}

int	double_left(char *delimiter)
{
	char	**heredoc;
	char	*str;
	int		fd;
	int		i;

	str = get_heredoc(delimiter);
	heredoc = ft_split(str, '\n');
	free(str);
	fd = open(".heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (perror("open"), 0);
	i = -1;
	while (heredoc[++i])
	{
		write(fd, heredoc[i], ft_strlen(heredoc[i]));
		write(fd, "\n", 1);
	}
	close(fd);
	fd = open(".heredoc.txt", O_RDONLY);
	if (fd == -1)
		return (perror("open"), 0);
	power_free(heredoc);
	return (fd);
}
