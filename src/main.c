/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/31 15:13:26 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "minishell.h"
#include "node.h"
#include "print.h"
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

void	init_tokenizer(t_tokenizer *tok)
{
	tok->cursor = 0;
	tok->state = TEXT;
	tok->next_token = NULL;
}

void	free_lists(t_list **lst1, t_node **lst2)
{
	ft_lstclear(lst1, ft_str_free);
	nodeclear(lst2);
}

int	main(int argc, char **argv, char **env)
{
	t_tokenizer	tok;
	t_list		*lst;
	t_node		*cmds;

	(void)argc;
	(void)argv;
	(void)env;
	tok.str = NULL;
	cmds = NULL;
	while (true)
	{
		init_tokenizer(&tok);
		tok.str = get_line(tok.str);
		if (!*tok.str)
			continue ;
		lst = tokenize(&tok);
		if (lst)
		{
			cmds = parse(lst);
			print_nodes(cmds);
		}
		free_lists(&lst, &cmds);
	}
	free(tok.str);
}
