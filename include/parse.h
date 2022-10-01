#ifndef PARSE_H
# define PARSE_H

# include "node.h"

t_node	*parse(t_list *tokens);
bool	is_valid_syntax(t_list *tokens);
char	*interpolate(char *str);
void	interpolate_arr(char **arr);
void	interpolate_redirs(t_list *redirs);

#endif
