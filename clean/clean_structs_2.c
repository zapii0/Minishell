/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:30:49 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/20 17:11:04 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

void	free_single_data(t_data *data)
{
	if (data->args)
		free_str_array(data->args);
	if (data->red_out)
		free_str_array(data->red_out);
	if (data->red_in)
		free_str_array(data->red_in);
	if (data->heredoc)
		free(data->heredoc);
}

void	clean_all(t_base *base, t_lex *lex)
{
	t_lex	*tmp;

	if (base)
	{
		free_base(base);
	}
	if (lex)
	{
		while (lex)
		{
			if (lex->content)
				free(lex->content);
			tmp = lex;
			lex = lex->next;
			free(tmp);
		}
	}
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

void	swapper_clean(char *a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
}
