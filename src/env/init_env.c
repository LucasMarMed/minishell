/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:52:29 by resilva           #+#    #+#             */
/*   Updated: 2024/08/26 12:14:14 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_split_env(char **envp, char **result, int *i)
{
	int	size_name;
	int	size_content;

	size_name = ft_strchr(envp[*i], '=') - envp[*i];
	size_content = ft_strlen(envp[*i]) - (size_name + 1);
	result = (char **)malloc(sizeof(char *) * 3);
	if (!result)
		exit(EXIT_FAILURE);
	result[0] = ft_substr(envp[*i], 0, size_name);
	result[1] = ft_substr(envp[*i], size_name + 1, size_content);
	result[2] = NULL;
	return (result);
}

static void	malloc_name_content(t_env *env, char **envp, int i)
{
	while (envp[i++])
		env->size_env++;
	env->e_name = malloc(sizeof(char *) * (env->size_env + 1));
	if (!env->e_name)
		exit(EXIT_FAILURE);
	env->e_content = malloc(sizeof(char *) * (env->size_env + 1));
	if (!env->e_content)
		exit(EXIT_FAILURE);
}

static void	init_env(t_shell *shell, t_env *env, char **tmp, int i)
{
	malloc_name_content(env, shell->envp, 0);
	while (shell->envp[++i])
	{
		tmp = ft_split_env(shell->envp, NULL, &i);
		env->e_name[i] = ft_strdup(tmp[0]);
		env->e_content[i] = ft_strdup(tmp[1]);
		free_split(tmp);
		tmp = NULL;
	}
	env->e_name[i] = NULL;
	env->e_content[i] = NULL;
}

void	init_shell_and_env(t_shell *shell, t_env *env)
{
	ft_bzero(shell, sizeof(t_shell));
	g_exit = 0;
	shell->envp = __environ;
	init_env(shell, env, NULL, -1);
}
