/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:46:24 by laube             #+#    #+#             */
/*   Updated: 2021/09/18 04:26:41 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "node.h"

bool	main_control(t_node *phrase);
void	pipe_read(void);
void	pipe_write(void);
int		operation_control(void);
void	clean_fd(void);
void	get_dest(void);
void	clean_fd(void);
void	ft_cmd(t_node *node);

#endif
