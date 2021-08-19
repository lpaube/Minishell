/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:15:12 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/19 15:52:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"

typedef enum e_token_type
{
	STRING,
	REDIRECT,
	PIPE,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

t_list	*tokenize(char *line);

#endif
