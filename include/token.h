/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:37:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/26 03:03:19 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

typedef enum e_token_type
{
	STRING,
	REDIRECT,
	PIPE,
}	t_token_type;

typedef struct s_token
{
	t_string		value;
	t_token_type	type;
}	t_token;

void	free_token(void *t);
t_token	*new_token(t_string value, t_token_type type);

#endif
