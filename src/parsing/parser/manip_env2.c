/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:37 by dpinto            #+#    #+#             */
/*   Updated: 2025/01/23 12:45:48 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_var_name(t_env *node)
{
	int	i;

	if (!node)
		return ;
	if (node->txt == NULL)
		return ;
	i = 0;
	while (node->txt[i] != '=')
		i++;
	node->var_name = malloc((sizeof(char)) * i + 1);
	if (node->var_name == NULL)
		return ;
	i = 0;
	while (node->txt[i] != '=')
	{
		node->var_name[i] = node->txt[i];
		i++;
	}
	node->var_name[i] = '\0';
}

void	edit_pwd(t_env *mini_env, char **argv)
{
	t_env	*ptr;
	t_env	*last_node;
	char	*pwd;
	char	*full;

	if (!argv)
		return ;
	ptr = mini_env;
	pwd = getcwd(NULL, 0);
	while (ptr)
	{
		if (!ft_strncmp(ptr->txt, "PWD", 3) && ptr->txt[3] == '=')
		{
			free(ptr->var_value);
			ptr->var_value = ft_strdup(pwd);
			free(ptr->txt);
			ptr->txt = ft_strjoin("PWD=", ptr->var_value);
			return (free(pwd));
		}
		ptr = ptr->next;
	}
	full = ft_strjoin("PWD=", pwd);
	add_node_env(mini_env);
	last_node = last_env_node(mini_env);
	return (fill_last_node(last_node, "PWD", pwd, full), free(full), free(pwd));
}

t_env	*copy_env(char *original[], char **argv)
{
	int		i;
	t_env	*mini_env;
	t_env	*ptr;

	i = 0;
	if (!original || original[0] == NULL)
		return (env_not_exist(argv));
	mini_env = malloc(sizeof(t_env));
	if (mini_env == NULL)
		return (NULL);
	mini_env->next = NULL;
	while (original[i])
		i++;
	while (i > 1)
	{
		mini_env = add_node_env(mini_env);
		i--;
	}
	i--;
	ptr = mini_env;
	copy_original_to_mini(original, i, ptr);
	ptr = mini_env;
	create_var_name_and_value(ptr);
	edit_pwd(ptr, argv);
	return (mini_env);
}

int	ft_stcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (0);
	if (!str2)
		return (0);
	if (str1[0] == '\0')
		return (0);
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}
