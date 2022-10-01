#ifndef EXEC_H
# define EXEC_H

# include "node.h"

void	process_cmd(t_node *cmds);
void	ft_cmd(t_node *node);
bool	op_control(t_node *cmds);
bool	exec_redirections(t_list *redirs, int *pipe_fd);
bool	exec_heredocs(t_list *redirs, int stdin_fd);

void	fd_reset(void);
void	init_pipes(t_node *cmds);
void	close_pipes(t_node *cmds);

#endif
