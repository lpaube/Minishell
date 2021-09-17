/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:29:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 19:47:30 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <stdbool.h>

char	*ft_getenv(char *var);
void	ft_setenv(const char *var, const char *value);
char	*var_name(const char *var);
bool	is_valid_var_name(const char *var);

#endif
