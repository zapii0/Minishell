/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:23:12 by apieniak          #+#    #+#             */
/*   Updated: 2025/08/14 18:44:15 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(void)
{	

	 //PSEUDO KOD 
	 //**env_list lub *env_list[] to 2D array zawierajacy sciezki do kazdej zmiennej srodowiskowej
	 //informacje odnośnie tego będą płyneły ze sturktury


	int i = 0;

	while (__environ[i] != NULL)
	{
		printf("%s\n", __environ[i]);
		i++;
	}

	return (0);
}