/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:47:24 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 02:33:11 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

int	env_var_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	compare_to_env(t_heredoc *h, char *env[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if ((int)ft_strlen(h->tmp) == env_var_len(env[i]))
		{
			if (!strncmp(env[i], h->tmp, ft_strlen(h->tmp)))
			{
				j = ft_strlen(h->tmp) + 1;
				while (env[i][j])
				{
					j++;
					h->len++;
				}
				break ;
			}
		}
		i++;
	}
	if (h->input[h->i] == '$')
		h->dollar = true;
	free(h->tmp);
}

static void	get_len(t_heredoc *h, char *env[])
{
	int	k;

	h->tmp = (char *)malloc(sizeof(char) * h->j + 1);
	if (!h->tmp)
		return (print_perror("malloc"));
	k = 0;
	while (k < h->j)
	{
		h->tmp[k] = h->input[h->i_save];
		h->i_save++;
		k++;
	}
	h->tmp[k] = '\0';
	compare_to_env(h, env);
}

char	*heredoc_expand(t_heredoc *h, char *env[])
{
	h->i = 0;
	h->len = 0;
	h->tmp = NULL;
	h->dollar = false;
	while (h->input[h->i])
	{
		h->j = 0;
		if (h->input[h->i] == '$' && h->input[h->i + 1] && h->input[h->i + 1] \
		!= '$' && ft_isalnum(h->input[h->i + 1]))
		{
			h->i++;
			h->i_save = h->i;
			if (ft_isalpha(h->input[h->i]))
			{
				while (h->input[h->i] && h->input[h->i] != '$' \
				&& ft_isalnum(h->input[h->i]))
				{
					h->i++;
					h->j++;
				}
				get_len(h, env);
			}
			else
				h->i++;
		}
		else if (h->dollar == true)
			h->dollar = false;
		else
		{
			h->len++;
			h->i++;
		}
	}
	printf("FINAL LEN IS : %i\n", h->len);
	return (heredoc_expanded(h, env));
}
