/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:06:32 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:37:42 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HMAP_H
# define FT_HMAP_H

# include "../libft.h"

typedef struct s_hmap_
{
	t_list	**data;
	size_t	size;
	void	(*del)(void *);
}	t_hmap_;

typedef struct s_pair
{
	char	*key;
	void	*value;
}	t_pair;

t_list	**get_hmap_buckets(t_hmap map, const char *key);
size_t	get_hmap_index(t_hmap map, const char *key);
t_pair	*create_pair(const char *key, void *value);
void	delete_pair(void *pair, void (*del)(void *));

#endif
