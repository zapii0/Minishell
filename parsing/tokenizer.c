/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:30 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/14 14:22:39 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

static void	debug_print_str_array(char **arr, const char *name)
{
	int	i;

	printf("%s:", name);
	if (!arr)
	{
		printf(" (null)\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf(" [%d]='%s'", i, arr[i]);
		i++;
	}
	printf("\n");
}

static void	debug_print_data(t_data *d, int idx)
{
	printf("data[%d]:\n", idx);
	debug_print_str_array(d->args, "args");
	debug_print_str_array(d->red_in, "red_in");
	debug_print_str_array(d->red_out, "red_out");
	printf("heredoc: %s\n", d->heredoc ? d->heredoc : "(null)");
	printf("b_heredoc: %d\tappend: %d\n", d->b_heredoc, d->append);
}

static void	debug_print_base(t_base *base)
{
	int	i;

	if (!base)
	{
		printf("base: (null)\n");
		return ;
	}
	printf("d_counter: %d\n", base->d_counter);
	i = 0;
	while (i < base->d_counter)
	{
		debug_print_data(&base->data[i], i);
		i++;
	}
}

static int	process_line_tokens(char *line, t_lex *lex)
{
	int i;
	int res;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_limiter(line[i]))
		{
			res = node_filler(line, i, lex);
			if (res == -1)
				return (-1);
			i = res;
		}
	}
	return (0);
}

t_base	*tokenizer(char *line, t_lex *lex, t_env *envp)
{
	int		i;
	t_base	*base;
	t_lex  *lex_head;

	if (!envp)
		return (NULL);
	lex_head = lex;
	qoute_error(line);
	i = process_line_tokens(line, lex_head);
	if (i == -1)
		return (NULL);
	if (syntax_error(lex_head))
		return (NULL);
	if (lex_head->next && envp_filler(lex_head->next, envp) == -1)
		return (NULL);
	base = init_base(pipe_counter(lex_head->next));
	if (!base)
		return (NULL);
	if (lex_head->next)
		lex_head->next->previous = NULL;
	quote_remover(lex);
	lex = red_parser(lex_head->next, base);
	if (!lex)
		return (free_base(base), NULL);
	debug_print_base(base);
	return (base);
}
