/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:35:44 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/27 17:58:06 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	print_error(const char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	unexpected_token(const t_string token)
{
	t_string	msg;

	msg = ft_str_new(NULL);
	ft_str_append_cstr(msg, "syntax error near unexpected token \'");
	ft_str_append(msg, token);
	ft_str_add_back(msg, '\'');
	print_error(ft_str_data(msg));
	ft_str_free(msg);
}
