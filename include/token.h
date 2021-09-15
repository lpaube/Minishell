/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:37:24 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 21:24:32 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "libft.h"

typedef enum e_type
{
	PIPE,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
	STRING,
}	t_type;

t_type	get_type(t_string token);
bool	is_redirection(t_type type);
char	*type_str(t_type type);

#endif
