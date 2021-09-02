/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:50:36 by laube             #+#    #+#             */
/*   Updated: 2021/08/31 18:57:30 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	pipe_write(t_phrase *phrase)
{
	int	saved_stdout;

	saved_stdout = dup(1);
	if (pipe(phrase->fd) == -1)
		print_error("pipe error");
	dup2(phrase->fd[1], 1);
	execution_control(phrase);
	dup2(saved_stdout, 1);
	close(phrase->fd[1]);
}

void	pipe_read(t_phrase *phrase)
{
	int	saved_stdin;

	saved_stdin = dup(0);
	dup2(phrase->prev->fd[0], 0);
	if (phrase->next && phrase->op == '|')
	{
		pipe_write(phrase);
	}
	else
	{
		execution_control(phrase);
	}
	dup2(saved_stdin, 0);
	close(phrase->prev->fd[0]);
}

/*
int	main(int argc, char **argv, char **env)
{
	t_phrase	*phrase1;
	t_phrase	*phrase2;
	char *test_args1[2] = {"ls", NULL};
	char *test_args2[3] = {"wc", "-w", NULL};

	errno = 0;

	phrase1 = malloc(sizeof(*phrase1));
	phrase1->fd = malloc(2 * sizeof(int));
	phrase1->bin = 1;
	phrase1->prev = NULL;
	phrase1->name = "ls";
	phrase1->op = '|';
	phrase1->args = test_args1;
	phrase1->env = dup_env_table(env, phrase1, 0);

	phrase2 = malloc(sizeof(*phrase2));
	phrase2->fd = malloc(2 * sizeof(int));
	phrase2->bin = 1;
	phrase2->next = NULL;
	phrase2->prev = phrase1;
	phrase2->name = "wc";
	phrase2->op = 0;
	phrase2->args = test_args2;
	phrase2->env = dup_env_table(env, phrase2, 0);

	phrase1->next = phrase2;

	main_control(phrase1);

	return (0);
}
*/
