/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:43:42 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 20:02:12 by mleblanc         ###   ########.fr       */
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
		print_args(lst->args);
		printf("\n");
		lst = lst->next;
	}
}
