/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:40:26 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 16:33:10 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, char *arg)
{
	char	cwd[MAX_PATH_SIZE];
	int		written;

	(void)shell;
	(void)arg;
	written = 0;
	if (getcwd(cwd, sizeof(cwd)))
		written = printf("%s\n", cwd);
	else
		perror("cwd");
	if (written < 0)
		return (1);
	return (0);
}

int	ft_exit(t_shell *shell, char *arg)
{
	int	ret;

	ret = 0;
	if (arg)
	{
		ret = ft_atoi(arg);
		free(arg);
	}
	if (shell->builtins)
		power_free(shell->builtins);
	if (shell->tokens)
		power_free(shell->tokens);
	if (shell->line)
		free(shell->line);
	if (shell->meta)
		free(shell->meta);
	if (shell->env)
		power_free(shell->env);
	exit(ret);
}

char	*check_path(char *path)
{
	int		i;
	char	*new_path;

	if ((path[0] == '.' && path[1] == '/')
		|| path[0] == '/')
		return (path);
	i = -1;
	new_path = malloc(sizeof(char) * ft_strlen(path) + 3);
	if (!new_path)
	{
		perror("malloc");
		exit (0);
	}
	new_path[0] = '.';
	new_path[1] = '/';
	while (path[++i])
		new_path[i + 2] = path[i];
	new_path[i + 2] = '\0';
	return (new_path);
}

char	*path_copy(char *dest, char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	dest = ft_calloc((i + 1), sizeof(char));
	if (!dest)
		return (perror("malloc"), NULL);
	i = 0;
	while (path[i])
	{
		dest[i] = path[i];
		i++;
	}
	return (dest);
}

int	ft_cd(t_shell *shell, char *path)
{
	char	*temp;

	temp = get_home_path(shell->env);
	if (!path || (((path[0] == '~' && path[1] == '/')
				|| (path[0] == '-' && path[1] == '-')) && !path[2]))
		chdir(temp);
	else if (path[0] == '/' && !path[1])
		chdir("/");
	else if (path[0] == '-' && !path[1])
	{
		free(temp);
		temp = path_copy(temp, shell->ex_path);
		printf("%s\n", shell->ex_path);
		getcwd(shell->ex_path, sizeof(shell->ex_path));
		chdir(temp);
	}
	else
	{
		path = check_path(path);
		getcwd(shell->ex_path, sizeof(shell->ex_path));
		if (chdir(path) == -1)
			return (free(temp), free(path), perror("chdir"), 1);
	}
	return (free(temp), update_pwd(shell));
}
