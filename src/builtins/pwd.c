/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:32:32 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 21:50:23 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "print.h"
#include <stdio.h>

#define CWD_BUFFER_SIZE (1024)

void	ft_pwd(t_node *node)
{
	char	cwd[CWD_BUFFER_SIZE];

	if (ft_strarr_size(node->args) > 1)
		print_error(PWD, NULL, "too many arguments");
	else if (getcwd(cwd, CWD_BUFFER_SIZE) != NULL)
		printf("%s\n", cwd);
	else
		print_error(PWD, NULL, strerror(errno));
}
