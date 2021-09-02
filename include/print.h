/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:41:41 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/31 18:33:39 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "libft.h"
# include "phrase.h"

void	print_token_list(const t_list *lst);
char	*op_name(t_operator op);
void	print_args(char **args);
void	print_nodes(const t_phrase *lst);

#endif
