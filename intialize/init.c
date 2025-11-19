/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:46:40 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/19 18:56:20 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->args = NULL;
	data->red_out = NULL;
	data->red_in = NULL;
	data->append = false;
	return (data);
}

void	init_single_data(t_data *data)
{
	data->args = NULL;
	data->red_out = NULL;
	data->red_in = NULL;
	data->b_heredoc = true;
	data->heredoc = NULL;
	data->append = false;
}

t_base	*init_base(int d_counter)
{
	t_base	*base;
	int		i;

	base = (t_base *)malloc(sizeof(t_base));
	if (!base)
		return (NULL);
	base->data = (t_data *)malloc(sizeof(t_data) * d_counter);
	if (!base->data)
		return (free(base), NULL);
	i = 0;
	while (i < d_counter)
		init_single_data(&base->data[i++]);
	base->d_counter = d_counter;
	base->exit_status = 0;
	base->pipes_num = 0;
	base->index = 0;
	base->evp = NULL;
	return (base);
}

int	pipe_counter(t_lex *lex)
{
	int	p_counter;

	p_counter = 0;
	while (lex)
	{
		if (lex->content && (!ft_strcmp("|", lex->content)))
			p_counter++;
		lex = lex->next;
	}
	if (p_counter == 0)
		return (1);
	else
		return (p_counter + 1);
}
