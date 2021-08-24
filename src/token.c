/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:39:24 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/24 16:57:58 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>

void	free_token(void *t)
{
	ft_strfree(((t_token *)t)->value);
	free(t);
}

t_token	*new_token(t_string value, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}
