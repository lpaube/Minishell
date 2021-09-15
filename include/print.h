/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:41:41 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 19:59:51 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "libft.h"
# include "node.h"

void	print_token_list(const t_list *lst);
void	print_args(char **args);
void	print_nodes(const t_node *lst);

#endif
