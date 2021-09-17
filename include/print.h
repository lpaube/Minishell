/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:27:28 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 17:52:43 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "node.h"
# include <sys/errno.h>

# define SHELL_NAME "Minishell"

void	print_error(const char *prg, const char *v1, const char *v2);
void	unexpected_token(const char *token);
void	print_cmds(const t_node *cmds);

#endif
