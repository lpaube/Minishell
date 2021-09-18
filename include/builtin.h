/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:45:01 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 04:10:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "node.h"

# define PWD "pwd"
# define CD "cd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

void	ft_echo(t_node *node);
void	ft_cd(t_node *node);
void	ft_unset(t_node *node);
void	ft_export(t_node *node);
void	ft_pwd(t_node *node);
void	ft_env(t_node *node);
bool	ft_exit(t_node *node);
void	process_error(const char *prg, const char *v1, const char *v2,
			bool *can_print);
#endif
