/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:16:25 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/24 17:47:08 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

# define SHELL_PROMPT ("minishell: ")

typedef struct s_parse
{
	char		*name;
	bool		is_builtin;
	char		**args;
	char		**opts;
}	t_parse;

#endif
