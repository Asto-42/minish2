/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:05:20 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/30 15:06:25 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_pp *pp, char *cmd, t_shell *shell)
{
	pp->tab = ft_split(cmd, ' ');
	pp->no_redirec = ignore_redirections(pp->tab, 0);
	pp->name = pp->tab[0];
	pp->cmd_name = get_cmd(pp->name, shell->env);
	check_redirect(cmd);
}
