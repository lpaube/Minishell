/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:27:28 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 20:30:51 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "node.h"
# include <sys/errno.h>

# define SHELL_NAME "minishell"

void	print_error(const char *prg, const char *v1, const char *v2);
void	unexpected_token(const char *token);
void	print_cmds(const t_node *cmds);

#endif
