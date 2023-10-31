/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 18:32:48 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(char *cmd)
{
	char	**cmdtab;
	int		i;
	int		fd;
	int		tmp_fd;

	cmdtab = ft_split(cmd, ' ');
	i = -1;
	fd = 0;
	tmp_fd = 0;
	while (cmdtab[++i])
	{
		tmp_fd = fd;
		fd = redirect(cmdtab, i);
		if (tmp_fd > 0 && tmp_fd != fd)
			close(tmp_fd);
	}
	power_free(cmdtab);
	return (fd);
}

void	child(t_pp *pp, t_shell *shell, char *cmd, int idx)
{
	int	i;

	i = -1;
	pp->pid = fork();
	if (pp->pid == 0)
	{
		do_the_redirections(pp);
		free(pp->pidtab);
		free(pp->pipe);
		if (call_builtins(shell, idx) == 7)
		{
			init_pipe(pp, cmd, shell);
			if (pp->no_redirec != NULL && pp->no_redirec[0] != NULL)
			{
				while (pp->no_redirec[++i])
					pp->no_redirec[i] = anti_douillax(pp->no_redirec[i]);
				execve(pp->cmd_name, pp->no_redirec, shell->env);
				printf("%s: command not found\n", pp->cmd_name);
				free_it(pp, ft_strdup("127"), shell);
			}
			free_it(pp, ft_strdup("0"), shell);
		}
		ft_exit(shell, ft_strdup("0"));
	}
	end_pipe(pp, pp->no_redirec, pp->tab, pp->cmd_name);
}

void	init_pidtab(t_pp *pp)
{
	int	i;

	i = -1;
	pp->pidtab = malloc(sizeof(int) * pp->cmd_nb);
	if (!pp->pidtab)
		perror("malloc");
	else
		while (++i < pp->cmd_nb)
			pp->pidtab[i] = 0;
}

void	wait_childs(t_pp *pp, t_shell *shell)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (pp->pidtab && ++i < pp->cmd_nb)
	{
		waitpid(pp->pidtab[i], &status, 0);
		if (WIFEXITED(status))
			shell->errno = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			shell->errno = WTERMSIG(status) + 128;
	}
	if (pp->pipe)
		free(pp->pipe);
	if (pp->pidtab)
		free(pp->pidtab);
}

int	ft_pipe(t_shell *shell)
{
	t_pp	pp;
	int		i;

	pp.cmd_nb = cmd_count(shell->tokens);
	if (pp.cmd_nb == 1 && !shell->tokens[1])
		return (0);
	pp.pipe_nb = 2 * (pp.cmd_nb - 1);
	pp.pipe = malloc(sizeof(int) * pp.pipe_nb);
	init_pidtab(&pp);
	if (!pp.pipe)
		return (perror("malloc"), 0);
	if (!pp.pidtab)
		return (free(pp.pipe), perror("malloc"), 0);
	create_pipes(&pp);
	pp.idx = -1;
	i = 0;
	while (++(pp.idx) < pp.cmd_nb)
	{
		child(&pp, shell, shell->tokens[i], i);
		i++;
	}
	close_pipes(&pp);
	wait_childs(&pp, shell);
	return (1);
}
