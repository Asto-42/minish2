/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:18:08 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/27 17:08:50 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    main_child(t_shell *shell)
{
    char    *cmd_name;
    char    *cmd;
    char    **nr;

    nr = ignore_redirections(ft_split(shell->tokens[0], ' '), 1);
    cmd = get_cmd(shell->tokens[0], shell->env);
    cmd_name = NULL;
    check_redirect(shell->tokens[0]);
    for (int i = 0; nr[i]; i++)
        nr[i] = anti_douillax(nr[i]);
    if (nr != NULL && nr[0] != NULL)
    {
        execve(cmd, nr, shell->env);
		shell->tokens[0] = anti_douillax(shell->tokens[0]);
        cmd_name = get_cmd(shell->tokens[0], shell->env);
        printf("%s: command not found\n", cmd_name);
        ft_exit(shell, ft_strdup("127"));
    }
    free(cmd_name);
    free(cmd);
    power_free(nr);
    ft_exit(shell, ft_strdup("0"));
}

void	main_core2(t_shell *shell, int status)
{
	shell->pid = fork();
	signal(SIGQUIT, SIG_DFL);
	if (shell->pid == 0)
		main_child(shell);
	else if (shell->pid > 0)
	{
		signal(SIGQUIT, SIG_IGN);
		if (ft_strncmp(shell->tokens[0], "./minishell", 11) == 0)
			signal(SIGINT, SIG_IGN);
		waitpid(shell->pid, &status, 0);
		init_signals();
	}
	if (WIFEXITED(status))
		shell->errno = WEXITSTATUS(status);
}

void	main_core(t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_strlen(shell->line))
		if (!ft_pipe(shell) && call_builtins(shell, 0) == 7)
			main_core2(shell, status);
}

void	prompt(t_shell *shell)
{
	if (!shell->errno)
		shell->line = readline(GREEN "→ " CYAN "minishell" RESET
				" [" GREEN "OK" RESET "] " BLUE "$> " RESET);
	else
		shell->line = readline(GREEN "→ " CYAN "minishell" RESET
				" [" RED "KO" RESET "] " BLUE "$> " RESET);
}
