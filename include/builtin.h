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
void	ft_exit(t_node *node);

#endif
