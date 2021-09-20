/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:33:08 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/20 03:20:15 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "node.h"
# include <sys/errno.h>

# define SHELL_NAME "minishell"

# define SUCCESS 0
# define GENERIC_ERR 1
# define SYNTAX_ERR 2
# define NOT_EXEC_ERR 126
# define ENVIRONMENT_ERR 127
# define NON_NUMERIC_ERR 255

# define BAD_IDENT "not a valid identifier"
# define TOO_MANY_ARGS "too many arguments"
# define NUMERIC_REQ "numeric argument required"
# define CMD_NOT_FOUND "command not found"
# define NO_HOME "HOME not set"
# define UNCLOSED_QUOTES "found unclosed quotes"
# define UNCLOSED_DQUOTES "found unclosed double quotes"

# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_HOME "HOME"

typedef struct s_minishell
{
	char			**env;
	unsigned int	code;
	int				stdin_fd;
	int				stdout_fd;
}	t_minishell;

extern t_minishell	g_mini;

char	*ft_getenv(const char *var);
void	ft_setenv(const char *var, const char *value);
char	*var_name(const char *var);
bool	is_valid_var_name(const char *var);

void	pset_err(const char *prg, const char *v1, const char *v2, int err);
void	unexpected_token(const char *token);

void	newline(int signal);
void	child_proc_quit(int signal);
void	child_proc_interrupt(int signal);

#endif
