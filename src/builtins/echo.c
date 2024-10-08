/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva < resilva@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:36 by resilva           #+#    #+#             */
/*   Updated: 2024/08/29 18:31:29 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_flag(char **argv, int *i)
{
	int	j;
	int	flag;

	flag = FALSE;
	while (*i < MAXARGS - 1 && !argv[*i])
		(*i)++;
	while (argv[*i] && !ft_strncmp(argv[*i], "-n", 2))
	{
		j = 1;
		while (argv[*i][j] == 'n')
		{
			j++;
			if (argv[*i][j] && argv[*i][j] != 'n')
				return (flag);
		}
		flag = TRUE;
		(*i)++;
		while (*i < MAXARGS - 1 && !argv[*i])
			(*i)++;
	}
	return (flag);
}

void	ms_echo(t_exec *cmd)
{
	int	i;
	int	break_l;

	i = 1;
	break_l = check_flag(cmd->argv, &i);
	while (i < MAXARGS - 1 && !cmd->argv[i])
		i++;
	while (cmd->argv[i])
	{
		if (i == 0)
			i++;
		if (cmd->argv[i])
			ft_putstr_fd(cmd->argv[i++], STDOUT_FILENO);
		while (i < MAXARGS - 1 && !cmd->argv[i])
			i++;
		if (cmd->argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!break_l)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit = 0;
}
