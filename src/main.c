/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/30 16:59:36 by mleblanc         ###   ########.fr       */
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

void	print_token_list(const t_list *lst)
{
	t_string		token;
	const t_list	*ptr;

	if (lst)
	{
		ptr = lst;
		while (ptr)
		{
			token = ptr->content;
			printf("%s\n", ft_str_data(token));
			ptr = ptr->next;
		}
	}
	printf("\n");
}

void	init_tokenizer(t_tokenizer *tok)
{
	tok->cursor = 0;
	tok->state = TEXT;
	tok->next_token = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_tokenizer	tok;
	t_list		*lst;
	t_dlist		*cmds;

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
			cmds = parse(lst);
			if (cmds)
			{
			}
		}
		ft_lstclear(&lst, ft_str_free);
		ft_dlstclear(&cmds, free_node);
	}
	free(tok.str);
	ft_lstclear(&lst, ft_str_free);
	ft_dlstclear(&cmds, free_node);
}
