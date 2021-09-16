/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:45:01 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 13:56:31 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "node.h"

void	ft_echo(t_node *node);
void	ft_cd(t_node *node);
void	ft_unset(t_node *node);
void	ft_export(t_node *node);
void	ft_pwd(void);
void	ft_env(void);
void	ft_exit(t_node *node);
bool	is_valid_var_name(const char *var);

#endif
