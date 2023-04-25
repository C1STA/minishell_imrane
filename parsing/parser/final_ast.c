/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 21:53:16 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/25 14:39:21 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_final	*create_final_ast(t_com **ast)
{
	t_final	*final;
	int		i;

	final = NULL;
	i = 0;
	while (ast[i])
	{
		final = create_list_final_ast(final, ast[i]);
		i++;
	}
	return (final);
}

t_final	*create_list_final_ast(t_final *final, t_com *ast)
{
	t_final	*ptr;
	t_final	*follow;

	ptr = malloc(sizeof(t_final));
	if (!ast)
		return (NULL);
	if (!final)
	{
		ptr -> cmds = break_linked_list_in_double_tab(ast);
		ptr -> redir = ast -> redir;
		ptr -> next = NULL;
		final = ptr;
	}
	else
	{
		follow = final;
		while (follow -> next != NULL)
			follow = follow -> next;
		follow -> next = ptr;
		ptr -> cmds = break_linked_list_in_double_tab(ast);
		ptr -> redir = ast -> redir;
		ptr -> next = NULL;
	}
	return (final);
}

char	**break_linked_list_in_double_tab(t_com *com)
{
	char	**tab;
	t_com	*follow;
	int		i;

	i = 0;
	if (!com)
		return (NULL);
	follow = com;
	tab = malloc(sizeof(char *) * (ft_com_len(com) + 1));
	while (follow)
	{
		if (follow -> txt)
		{
			tab[i] = malloc(sizeof(char) * (ft_strlen(follow -> txt) + 1));
			ft_strlcpy(tab[i], follow -> txt, (ft_strlen(follow -> txt) + 1));
			follow = follow -> next;
			tab[++i] = NULL;
		}
		else
		{
			tab[i] = NULL;
			follow = follow -> next;
		}
	}
	return (tab);
}

int	ft_com_len(t_com *com)
{
	t_com	*follow;
	int		i;

	i = 0;
	follow = com;
	while (follow)
	{
		i++;
		follow = follow -> next;
	}
	return (i);
}
