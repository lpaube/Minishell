/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:35:44 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/26 02:51:22 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <unistd.h>

void	print_error(const char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	unexpected_token(const t_token *token)
{
	t_string	msg;

	msg = ft_str_new(NULL);
	ft_str_append_cstr(msg, "syntax error near unexpected token \'");
	ft_str_append(msg, token->value);
	ft_str_add_back(msg, '\'');
	print_error(ft_str_data(msg));
	ft_str_free(msg);
}
