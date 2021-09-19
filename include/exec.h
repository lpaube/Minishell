/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:46:24 by laube             #+#    #+#             */
/*   Updated: 2021/09/18 22:25:16 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "node.h"
# include "libft.h"
# include "tokenizer.h"
# include <fcntl.h>
# include <stdlib.h>

bool	process_cmd(t_node *cmds);
bool	execute(t_node *node);
void	pipe_read(void);
void	pipe_write(void);
int		operation_control(void);
void	clean_fd(void);
void	get_dest(void);
void	clean_fd(void);
void	ft_cmd(t_node *node);

#endif
