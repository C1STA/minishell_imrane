/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:19:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/07 15:45:46 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	executor(t_final *cmds, t_env *mini_env)
{
	if (!ft_heredoc(cmds, mini_env))
		return ;
	pipex(cmds, mini_env);
	//printf("LE PID DU PROCESSUS PARENT EST : __________________%d\n", getpid());
	remove_heredoc(cmds);
}
