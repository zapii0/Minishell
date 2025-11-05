/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:30 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/05 01:35:58 by mzapora          ###   ########.fr       */
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

t_base	*tokenizer(char *line, t_lex *lex, t_env *envp)
{
	int		i;
	t_base	*base;

	if (!envp)
		return (NULL);
	i = 0;
	qoute_error(line);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_limiter(line[i]))
			i = node_filler(line, i, lex);
	}
	syntax_error(lex);
	envp_filler(lex, envp);
	base = init_base(pipe_counter(lex->next));
	if (!base)
		return (NULL);
	lex = red_parser(lex->next, base);
	debug_print_base(base);
	return (base);
}

    // t_lex *cur = lex->next;
    // while (cur)
    // {
    //     printf("content: %s\n", cur->content);
    //     cur = cur->next;
    // }
	