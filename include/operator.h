/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 04:10:20 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/27 17:53:59 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

# include "libft.h"

typedef enum e_operator
{
	PIPE,
	OUTPUT,
	APPEND,
	INPUT,
	READ,
	NONE,
}	t_operator;

t_operator	get_operator(t_string token);

#endif
