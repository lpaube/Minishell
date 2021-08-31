/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:26:49 by laube             #+#    #+#             */
/*   Updated: 2021/08/31 00:28:53 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include "../libft/libft.h"

typedef struct s_phrase	t_phrase;

struct	s_phrase
{
	int	bin;
	char		**env;
	char		*cmd;
	char		**cmd_args; // Needs to start with bin name, and be NULL terminated
	t_phrase	*next;
	t_phrase	*prev;
	char			op;
	int			*fd;
};

void	execution_control(t_phrase *phrase);
