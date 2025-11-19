/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:16:43 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/19 18:52:57 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

char	*handle_exit_status_exit(char *line, int *i, t_base *base)
{
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(base->exit_status));
	}
	return (NULL);
}

int	envp_filler(t_lex *lex, t_env *envp, t_base *base)
{
	while (lex)
	{
		if (lex->content && ft_strchr(lex->content, '$'))
			lex->content = envp_value_checker(lex->content, envp, base);
		if (lex->content == NULL)
			return (-1);
		lex = lex->next;
	}
	return (0);
}

char	*envp_value_checker(char *line, t_env *envp, t_base *base)
{
	int		i;
	bool	single_q;
	bool	double_q;

	i = 0;
	single_q = false;
	double_q = false;
	while (line && line[i])
	{
		if (line[i] == '\'' && !double_q)
			single_q = !single_q;
		if (line[i] == '"' && !single_q)
			double_q = !double_q;
		if (line[i] == '$' && !single_q)
		{
			line = envp_value_swapper(line, &i, envp, base);
			if (!line)
				return (NULL);
			if (i >= (int)ft_strlen(line))
				break ;
			continue ;
		}
		i++;
	}
	return (line);
}

char	*envp_value_swapper(char *line, int *i, t_env *envp, t_base *base)
{
	char	*first;
	char	*second;
	char	*third;
	char	*tmp;

	first = get_first(line, *i);
	second = get_second(line, i, envp, base);
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
