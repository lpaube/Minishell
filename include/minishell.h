/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:33:08 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 06:22:57 by mleblanc         ###   ########.fr       */
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
# define ENV_ERR 127

typedef struct s_minishell
{
	char			**env;
	unsigned char	code;
	int				*fd;
	int				saved_stdin;
	int				saved_stdout;
	int				allow_signal;
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
