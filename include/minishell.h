/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:33:08 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 15:35:47 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "phrase.h"

typedef struct s_minishell
{
	char		**env;
	int			code;
	int			*fd;
	int			saved_stdin;
	int			saved_stdout;
	t_phrase	*phrase;
	int			allow_signal;
}	t_minishell;

extern t_minishell	g_minishell;

char	*ft_getenv(char *var);

#endif