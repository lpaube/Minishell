/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:11:20 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 22:11:41 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "node.h"

t_node	*parse(t_list *tokens);
bool	is_valid_syntax(t_list *tokens);
char	*interpolate(char *str);
void	interpolate_arr(char **arr);
void	interpolate_redirs(t_list *redirs);

#endif
