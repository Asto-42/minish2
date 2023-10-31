/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/31 12:09:45 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	builtchild(int i, t_shell *shell, char *arg, int idx)
{
	int	status;
	int	pid;
	int	do_exit;

	status = 0;
	pid = 0;
	do_exit = 0;
	if (i != 1 && i != 3 && i != 4 && i != 6)
	{
		pid = fork();
		do_exit = 1;
	}
	if (pid == 0)
	{
		check_redirect(shell->tokens[idx]);
		arg = anti_douillax(arg);
		shell->errno = shell->f_ptr[i](shell, arg);
		if (do_exit || i == 6)
			patch(shell, arg);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status) && do_exit)
		shell->errno = WEXITSTATUS(status);
	print_write_error(shell, i);
}

int	call_builtins(t_shell *shell, int idx)
{
	int		i;
	char	*arg;
	char	**tab;

	i = -1;
	arg = init_builtins(shell->tokens[idx]);
	tab = ft_split(shell->tokens[idx], ' ');
	while (ft_strlen(shell->tokens[idx]) && shell->builtins[++i])
	{
		if (mnsh_strcmp(shell->builtins[i], tab[0]) == 0)
		{
			if (i == 6)
				printf("exit\n");
			power_free(tab);
			builtchild(i, shell, arg, idx);
			free(arg);
			return (0);
		}
	}
	power_free(tab);
	if (arg && ft_strlen(arg))
		free(arg);
	return (i);
}

void	start_loop(t_shell *shell)
{
	g_signal = 1;
	prompt(shell);
	if (shell->line == NULL)
		ft_exit(shell, NULL);
	add_history(shell->line);
	shell->line = douillax(shell->line);
	shell->badline_errno = badline(shell->line, shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	ft_init_struct(&shell);
	init_shell(&shell, env);
	while (ac && av[0])
	{
		start_loop(&shell);
		if (shell.badline_errno != -42)
		{
			shell.tokens = ft_split_quote(&shell, shell.line);
			if (shell.tokens && shell.tokens[0])
			{
				g_signal = 0;
				main_core(&shell);
				if (shell.tokens)
					power_free(shell.tokens);
				shell.tokens = NULL;
			}
			if (shell.tokens != NULL)
				power_free(shell.tokens);
		}
		else
			shell.errno = 2;
	}
	return (0);
}
