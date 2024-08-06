/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:58:35 by resilva           #+#    #+#             */
/*   Updated: 2024/07/31 15:32:57 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	ft_count_tokens(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	return (i);
}

void	ft_skip_space(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

void	ft_exec_cd(char *cmd, char *path, int ntokens)
{
	int	i;

	i = 0;
	while(cmd[i])
		i++;
	if (i == 2)
	{
		if (ntokens >= 3)
		{
			ft_error(cmd, NULL, "too many arguments");
			return ;
		}
		if (!path)
			path = getenv("HOME");
		else if (*path == '~')
			if (path[1] == '/' || !path[1])
				path = getenv("HOME");
		if (chdir(path))
			perror("chdir");
	}
	else
		ft_error(cmd, NULL, "command not found");
}

void	ft_exec_pwd(char *cmd)
{
	char	path[1024];
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 3)
	{
		if (getcwd(path, sizeof(path)))
		{
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			perror("getcwd");
	}
	else
		ft_error(cmd, NULL, "command not found");
}

void	ft_exec_echo(char **cmd_args, char *cmd, int ntokens, int len_cmd)
{
	int	i;

	if (len_cmd == 4)
	{
		i = 1;
		if (ntokens == 1)
			ft_putchar_fd('\n', STDIN_FILENO);
		else
		{
			while (--ntokens)
			{
				ft_putstr_fd(cmd_args[i++], STDIN_FILENO);
				ft_putchar_fd(' ', STDIN_FILENO);
			}
			ft_putchar_fd('\n', STDIN_FILENO);
		}
	}
	else
		ft_error(cmd, NULL, "command not found");
}

void	ft_exec_env(t_shell *shell, char *cmd, int len_cmd, int i)
{
	if (len_cmd == 3)
	{
		while (shell->envp[++i])
		{
			ft_putstr_fd(shell->env.e_name[i], STDIN_FILENO);
			ft_putchar_fd('=', STDIN_FILENO);
			ft_putstr_fd(shell->env.e_content[i], STDIN_FILENO);
			ft_putchar_fd('\n', STDIN_FILENO);
			
		}
	}
	else
		ft_error(cmd, NULL, "command not found");
}

void	ft_exec_exit(t_shell *shell, char *cmd, char *arg, int ntokens)
{
	int	len_cmd;

	len_cmd = ft_strlen(cmd);
	if (len_cmd == 4)
	{
		if (ntokens > 2)
			ft_error(cmd, NULL, "too many arguments");
		else
			clean_exit(shell, arg);
	}
	else
		ft_error(cmd, NULL, "command not found");
}

void	ft_exec_cmd(t_shell *shell, char *line)
{
	char	**cmd_args;
	char	*arg1;
	char	*cmd;
	int		ntokens;

	cmd_args = ft_split(line, ' ');
	cmd = ft_strdup(cmd_args[0]);
	arg1 = NULL;
	if (cmd_args[1])
		arg1 = ft_strdup(cmd_args[1]);
	ntokens = ft_count_tokens(cmd_args);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_exec_cd(cmd, arg1, ntokens);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_exec_pwd(cmd);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		ft_exec_echo(cmd_args, cmd, ntokens, ft_strlen(cmd));
	else if (!ft_strncmp(cmd, "env", 3))
		ft_exec_env(shell, cmd, ft_strlen(cmd), -1);
	else if (!ft_strncmp(cmd, "exit", 4))
		ft_exec_exit(shell, cmd, arg1, ntokens);
	free_split(cmd_args);
	free(cmd);
	free(arg1);
}