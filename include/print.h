/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:41:41 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 21:16:17 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "node.h"

void	*print_error(const char *msg);
void	*unexpected_token(const char *token);
void	print_cmds(const t_node *cmds);

#endif
