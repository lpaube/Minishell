/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:33:08 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 23:27:46 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "node.h"

# define SHELL_NAME "minishell"

# define GENERIC_ERR 1
# define SYNTAX_ERR 2
# define ENV_ERR 127

typedef struct s_minishell
{
	char		**env;
	int			code;
	int			*fd;
	int			saved_stdin;
	int			saved_stdout;
	int			allow_signal;
}	t_minishell;

extern t_minishell	g_mini;

void	newline(int signal);
void	nothing(int signal);

#endif
