/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:19:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/23 01:34:10 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	executor(t_final *cmds, char *env[])
{
	cmds->exit_tmp = g_exit_status;
	if (!ft_heredoc(cmds, env))
		return (remove_heredoc(cmds));
	pipex(cmds, env);
	remove_heredoc(cmds);
}
