/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_allocated.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:23:17 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/19 17:27:25 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_string_array(char **arr)
{
    int	i;

    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void	clear_data_element(t_data *data)
{
    if (data->args)
        free_string_array(data->args);
    if (data->red_in)
        free_string_array(data->red_in);
    if (data->red_out)
        free_string_array(data->red_out);
    if (data->heredoc)
        free(data->heredoc);
}

void	clear_all_allocated(t_base *base)
{
    int	i;

    if (!base || !base->data)
        return ;
    i = 0;
    while (i < base->d_counter)
    {
        clear_data_element(&base->data[i]);
        i++;
    }
    if (base->evp)
        free_string_array(base->evp);
}