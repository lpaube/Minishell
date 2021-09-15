/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:43:42 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 22:36:07 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdio.h>

void	*print_error(const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (NULL);
}

void	*unexpected_token(const char *token)
{
	t_string	msg;

	msg = ft_str_new(NULL);
	ft_str_append_cstr(msg, "syntax error near unexpected token \'");
	ft_str_append_cstr(msg, token);
	ft_str_add_back(msg, '\'');
	print_error(ft_str_data(msg));
	ft_str_free(msg);
	return (NULL);
}

static void	print_redir(void *redir)
{
	t_redir	*r;

	r = redir;
	printf("File: %s - type: %s\n", r->file, type_str(r->type));
}

void	print_cmds(const t_node *cmds)
{
	int	i;

	while (cmds)
	{
		printf("Cmd: %s\n", cmds->cmd);
		i = 0;
		while (cmds->args[i])
		{
			printf("Arg%d: %s\n", i, cmds->args[i]);
			++i;
		}
		ft_lstiter(cmds->redirs, print_redir);
		cmds = cmds->next;
	}
}
