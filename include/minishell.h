/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:16:25 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/26 02:50:33 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

# define SHELL_PROMPT "minishell: "

typedef struct s_phrase
{
	char	*name;
	char	**args;
	bool	is_cmd;
}	t_phrase;

void	print_error(const char *msg);
void	unexpected_token(const t_token *token);

#endif
