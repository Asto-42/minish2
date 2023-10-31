/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:18:51 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/31 11:35:52 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_shell *shell, char *arg)
{
	int		x;
	int		n;
	char	**tab;
	int		wr;

	x = -1;
	(void)shell;
	wr = 0;
	if (!arg || ft_strncmp(arg, "", 1) == 0)
		return (printf("\n"), 0);
	tab = ft_split(arg, ' ');
	if (ft_strncmp(tab[0], "-n", 2) == 0 && !tab[1])
		return (power_free(tab), 0);
	if (ft_strncmp(tab[0], "-n", 2) == 0)
		n = ++x + 1;
	else
		n = 0;
	while (tab[++x + 1])
		if (ft_strncmp(tab[x], "-n", 2) || wr)
			wr = printf("%s ", tab[x]);
	if (ft_strncmp(tab[x], "-n", 2) || wr)
		wr = printf("%s", tab[x]);
	if (n != 1)
		wr = printf("\n");
	return (power_free(tab), is_neg(wr));
}

int	update_pwd(t_shell *shell)
{
	char	*pwd;
	char	cwd[MAX_PATH_SIZE];
	char	*opwd;

	opwd = str_add("OLDPWD=", shell->ex_path, 0, 0);
	getcwd(cwd, MAX_PATH_SIZE);
	pwd = str_add("PWD=", cwd, 0, 0);
	ft_export(shell, opwd);
	ft_export(shell, pwd);
	free(pwd);
	free(opwd);
	return (0);
}
