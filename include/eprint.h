/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eprint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:27:28 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 23:25:59 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EPRINT_H
# define EPRINT_H

# include "node.h"
# include <string.h>
# include <sys/errno.h>

void	pset_err(const char *prg, const char *v1, const char *v2, int err);
void	unexpected_token(const char *token);

#endif
