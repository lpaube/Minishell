/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:16:25 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/30 16:10:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "operator.h"
# include <stdbool.h>

# define SHELL_PROMPT "minishell: "

typedef struct s_node
{
	char		*name;
	char		**args;
	t_operator	op;
}	t_node;

void	print_error(const char *msg);
void	unexpected_token(const t_string token);
void	free_node(void *node);

#endif
