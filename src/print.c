/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:43:42 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/31 01:44:47 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "stdio.h"

void	print_token_list(const t_list *lst)
{
	t_string	token;

	while (lst)
	{
		token = lst->content;
		printf("%s\n", ft_str_data(token));
		lst = lst->next;
	}
	printf("\n");
}

char	*op_name(t_operator op)
{
	if (op == PIPE)
		return ("PIPE");
	if (op == OUTPUT)
		return ("OUTPUT");
	if (op == APPEND)
		return ("APPEND");
	if (op == INPUT)
		return ("INPUT");
	if (op == READ)
		return ("READ");
	return ("NONE");
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("Arg %d: %s\n", i, args[i]);
		++i;
	}
}

void	print_nodes(const t_node *lst)
{
	while (lst)
	{
		printf("Cmd: %s - Operator: %s\n", lst->name, op_name(lst->op));
		print_args(lst->args);
		printf("\n");
		lst = lst->next;
	}
}
