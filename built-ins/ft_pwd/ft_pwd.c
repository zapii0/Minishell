/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:22:10 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/11 19:44:08 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = save_env_value("PWD", env);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		return (0);
	}
	printf("\n");
	return (1);
}
