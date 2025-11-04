/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:58:50 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/02 01:04:45 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    free(base->heredoc);
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
