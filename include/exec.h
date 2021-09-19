/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:46:24 by laube             #+#    #+#             */
/*   Updated: 2021/09/19 18:26:14 by laube            ###   ########.fr       */
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
void	op_control(t_node *cmds);
void	redir_output(t_redir *redir);
void	redir_append(t_redir *redir);
void	redir_input(t_redir *redir);
void	redir_heredoc(t_redir *redir);

#endif
