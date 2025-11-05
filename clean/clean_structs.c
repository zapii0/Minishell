/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:58:50 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/05 01:18:37 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

void	free_single_data(t_data *data)
{
    free_str_array(data->args);
    free_str_array(data->red_out);
    free_str_array(data->red_in);
}

void	free_base(t_base *base)
{
    int	i;

    if (!base)
        return ;
    i = 0;
    while (i < base->d_counter)
        free_single_data(&base->data[i++]);
    free(base->data);
    free(base);
}

void	free_str_array(char **arr)
{
    int	i;

    if (!arr)
        return ;
    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

t_lex	*clean_redirects(t_lex *lex)
{
	t_lex	*head;

	head = lex;
	while (lex)
	{
		if (lex->content && (is_in_red(lex->content) || \
			is_out_red(lex->content) || !ft_strcmp("<<", lex->content)))
		{
			lex = clean_two_nodes(lex, &head);
			continue;
		}
		lex = lex->next;
	}
	return (head);
}

t_lex	*clean_two_nodes(t_lex *current, t_lex **head)
{
	t_lex	*first;
	t_lex	*second;
	t_lex	*safe;

	first = current;
	second = current->next;
	safe = second->next;
	if (first->previous)
		first->previous->next = safe;
	else
		*head = safe;
	if (safe)
		safe->previous = first->previous;
	free(first->content);
	free(first);
	free(second->content);
	free(second);
	return (safe);
}
