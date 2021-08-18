/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/18 19:08:21 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#define SHELL_PROMPT ("minishell: ")

char	*get_line(char *line)
{
	char	*tmp;

	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(SHELL_PROMPT);
	tmp = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	line = tmp;
	if (line && *line)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*lst;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	while (true)
	{
		line = get_line(line);
		lst = tokenize(line);
		if (!lst)
			printf("BAD\n");
		if (ft_strncmp("exit", line, ft_strlen(line)) == 0)
			break ;
	}
	free(line);
}
