/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:30 by mzapora           #+#    #+#             */
/*   Updated: 2025/10/28 17:23:24 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"


void	tokenizer(char *line, t_lex *lex, t_env *envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	qoute_error(line);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_limiter(line[i]))
			i = node_filler(line, i, lex);
	}
	syntax_error(lex);

    t_lex *cur = lex->next; // pomijamy dummy node
    while (cur)
    {
        printf("content: %s\n", cur->content);
        cur = cur->next;
    }
	//envp_filler(lex, envp);
	return ;
}

void	envp_filler(t_lex *lex, t_env *envp)
{
	int	i;

	i = 0;
	while (lex)
	{
		if(lex->content && ft_strchr(lex->content, '$'))
			lex->content = envp_value_swap(lex->content);
		lex = lex->next;
	}
}

char	*envp_value_checker(char *line)
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
			line = envp_value_swapper(line, &i);
		i++;
	}
}

char	*envp_value_swapper(char *line, int *i)
{
	char	*first;
	char	*second;
	char	*third;

	first = get_first(line, i);
	second = get_second(line, *i);
	third = get_third(line, i);
}

char	*get_first(char *line, int i)
{
	char	*str;
	int		j;

	j = 0;
	while (j < i)
		j++;
	if (j == 0)
		return (ft_strdup(""));
	str = calloc(j + 1, 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_second(char *line, int *i)
{
	int		j;
	int		k;
	char	*name;

	j = 0;
	k = 0;
	(*i)++;
	while (ft_isalnum(line[(*i) + j]) || line[(*i) + j] == '_')
		j++;
	name = calloc(j + 1, 1);
	if (!name)
		return (NULL);
	while (k < j)
	{
		name[k] = line[k + (*i)];
		k++;
	}
	name[k] = '\0';
	
}
