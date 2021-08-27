/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/27 18:02:54 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

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

void	print_token_list(t_list *lst)
{
	t_string	token;
	t_list		*ptr;

	if (lst)
	{
		ptr = lst;
		while (ptr)
		{
			token = (t_string)ptr->content;
			printf("%s\n", ft_str_data(token));
			ptr = ptr->next;
		}
	}
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
	t_tokenizer	tok;
	t_tree		*ast;

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
		if (ft_strncmp("exit", tok.str, 5) == 0)
			break ;
		if (lst)
		{
			print_token_list(lst);
			ast = parse(lst);
		}
		ft_lstclear(&lst, ft_str_free);
	}
	free(tok.str);
	ft_lstclear(&lst, ft_str_free);
}
