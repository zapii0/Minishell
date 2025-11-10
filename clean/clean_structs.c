/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:58:50 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/05 20:20:12 by mzapora          ###   ########.fr       */
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

static int	is_redirect_op(char *content)
{
	if (!content)
		return (0);
	if (is_in_red(content) || is_out_red(content) || !ft_strcmp("<<", content))
		return (1);
	return (0);
}

static t_lex	*create_node_copy(t_lex *src, t_lex *tail)
{
	t_lex	*new;

	new = malloc(sizeof(t_lex));
	if (!new)
		return (NULL);
	new->content = src->content;
	new->type = src->type;
	new->next = NULL;
	new->previous = tail;
	return (new);
}

static void	add_to_list(t_lex **head, t_lex **tail, t_lex *new)
{
	if (!*head)
		*head = new;
	if (*tail)
		(*tail)->next = new;
	*tail = new;
}

t_lex	*clean_redirects(t_lex *lex)
{
	t_lex	*head;
	t_lex	*new_list;
	t_lex	*tail;

	head = NULL;
	tail = NULL;
	while (lex)
	{
		if (is_redirect_op(lex->content))
		{
			lex = lex->next;
			if (lex)
				lex = lex->next;
			continue;
		}
		if (lex->content)
		{
			new_list = create_node_copy(lex, tail);
			if (!new_list)
				return (head);
			add_to_list(&head, &tail, new_list);
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
	if (!second)
		return (NULL);
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
