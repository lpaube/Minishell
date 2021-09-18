/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:29:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 04:40:28 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdbool.h>

char	*ft_getenv(const char *var);
void	ft_setenv(const char *var, const char *value);
char	*var_name(const char *var);
bool	is_valid_var_name(const char *var);

#endif
