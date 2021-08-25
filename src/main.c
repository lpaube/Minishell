/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/25 15:38:19 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

void	free_token(void *t);

char	*get_line(char *line)
{
	char	*tmp;

	if (line)
		free(line);
	line = readline(SHELL_PROMPT);
	tmp = ft_strtrim(line, WHITESPACE);
	free(line);
	line = tmp;
	if (line && *line)
		add_history(line);
	return (line);
}

void	init_tokenizer(t_tokenizer *tok)
{
	tok->cursor = 0;
	tok->state = TEXT;
	tok->next_token = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_list		*lst;
	t_list		*ptr;
	t_tokenizer	tok;
	t_token		*token;

	(void)argc;
	(void)argv;
	(void)env;
	tok.str = NULL;
	while (true)
	{
		init_tokenizer(&tok);
		tok.str = get_line(tok.str);
		if (!*tok.str)
			continue ;
		lst = tokenize(&tok);
		if (lst)
		{
			ptr = lst;
			while (ptr)
			{
				token = (t_token *)ptr->content;
				printf("%s - %d\n", ft_str_data(token->value), token->type);
				ptr = ptr->next;
			}
		}
		if (ft_strncmp("exit", tok.str, 5) == 0)
			break ;
		ft_lstclear(&lst, free_token);
	}
	free(tok.str);
	ft_lstclear(&lst, free_token);
}
