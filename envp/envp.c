/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:16:43 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/14 14:22:12 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

int	envp_filler(t_lex *lex, t_env *envp)
{
	while (lex)
	{
		if (lex->content && ft_strchr(lex->content, '$'))
			lex->content = envp_value_checker(lex->content, envp);
		if (lex->content == NULL)
			return (-1);
		lex = lex->next;
		// if (quote_remover(lex))
		// 	return (-1);
	}
	return (0);
}

char	*envp_value_checker(char *line, t_env *envp)
{
	int 	i;
	bool	single_q;
	bool	double_q;
	
	i = 0;
	single_q = false;
	double_q = false;
	while (line[i])
	{
		if (line[i] == '\'' && !double_q)
			single_q = !single_q;
		if (line[i] == '"' && !single_q)
			double_q = !double_q;
		if (line[i] == '$' && !single_q)
			line = envp_value_swapper(line, &i, envp);
		i++;
	}
	return (line);
}

char	*envp_value_swapper(char *line, int *i, t_env *envp)
{
	char	*first;
	char	*second;
	char	*third;
	char	*tmp;

	first = get_first(line, *i);
	second = get_second(line, i, envp);
	third = get_third(line, *i);
	if (!first || !second || !third)
	{
		swapper_clean(first, second, third);
		return (NULL);
	}
	tmp = ft_strjoin(first, second);
	if (!tmp)
		return (swapper_clean(first, second, third), NULL);
	free(line);
	line = tmp;
	tmp = ft_strjoin(tmp, third);
	free(line);
	swapper_clean(first, second, third);
	return (tmp);
}
