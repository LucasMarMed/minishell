/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:26:27 by resilva           #+#    #+#             */
/*   Updated: 2024/08/27 22:07:03 by resilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(t_shell *sh, char *msg, char *msg2, int exit)
{
	ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (msg2)
	{
		if (msg2[0])
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	ft_putendl_fd(msg2, STDERR_FILENO);
	sh->status = RESTORE;
	g_exit = exit;
	return (TRUE);
}

int	print_error_syntax(t_shell *sh, char *msg, int exit)
{
	int	len;

	len = ft_strlen(msg);
	ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	if (!*msg)
		ft_putstr_fd("newline", STDERR_FILENO);
	else if (len > 1 && (*(msg + 1) == *msg || *(msg - 1) == *msg) && \
			*msg != '(' && *msg != ')')
	{
		ft_putchar_fd(*msg, STDERR_FILENO);
		ft_putchar_fd(*msg, STDERR_FILENO);
	}
	else
		ft_putchar_fd(*msg, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	sh->status = RESTORE;
	g_exit = exit;
	return (TRUE);
}

int	print_error_export(t_shell *sh, char *cmd, char *arg, int exit)
{
	ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	sh->status = RESTORE;
	g_exit = exit;
	return (TRUE);
}

int	print_error_unsupport(t_shell *sh, char *msg, int exit)
{
	ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
	ft_putstr_fd("no support for operator `", STDERR_FILENO);
	ft_putchar_fd(*msg, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	sh->status = RESTORE;
	g_exit = exit;
	return (TRUE);
}
