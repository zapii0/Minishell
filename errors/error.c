/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:01:24 by mzapora           #+#    #+#             */
/*   Updated: 2025/10/21 06:21:47 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parsing.h"


void	qoute_error(char *line)
{
	int		i;
	char	limiter;
	bool	open;

	i = -1;
	open = false;
	while (line[++i])
	{
		if ((line[i] == '"' || line[i] == '\'') && open == false)
		{
			limiter = line[i];
			open = true;
		}
		else if (line[i] == limiter && open == true)
		{
			limiter = '\0';
			open = false;
		}
	}
	if (open == true && limiter == '\'')
		error_exec(QUOTE_ERROR, 0);
	if (open == true && limiter == '\"')
		error_exec(QUOTE_ERROR, 1);
	return ;
}

void	error_exec(int error_code, int mess_code)
{
	if (error_code == QUOTE_ERROR && mess_code == 0)
		write(2, "syntax error unclosed quote `'\''\n", 33);
	if (error_code == QUOTE_ERROR && mess_code == 1)
		write(2, "syntax error unclosed quote `\"'\n", 32);
	if (error_code == PIPE_ERROR)
		write(2, "syntax error near unexpected token `|'\n", 40);
	if (error_code == RED_ERROR && mess_code == 1)	
		write(2, "syntax error near unexpected token `<'\n", 40);
	if (error_code == RED_ERROR && mess_code == 0)	
		write(2, "syntax error near unexpected token `>'\n", 40);
	if (error_code == RED_ERROR && mess_code == 3)	
		write(2, "syntax error near unexpected token `>>'\n", 41);
	if (error_code == RED_ERROR && mess_code == 4)	
		write(2, "syntax error near unexpected token `<<'\n", 41);
	if (error_code == RED_ERROR && mess_code == 5)	
		write(2, "syntax error near unexpected token `><'\n", 41);
	if (error_code == RED_ERROR && mess_code == 6)	
		write(2, "syntax error near unexpected token `<>`\n", 41);
	if (error_code == RED_ERROR && mess_code == 7)	
		write(2, "syntax error near unexpected token `newline'\n", 46);
}

void	error_red2(t_lex *lex)
{
	if (!lex || !lex->next || !lex->next->content)
		return ;
	if (lex->next->content[1] && !ft_strncmp(">>", lex->next->content, 3))
		return (error_exec(RED_ERROR, 3));
	if (lex->next->content[1] && !ft_strncmp("<<", lex->next->content, 3))
		return (error_exec(RED_ERROR, 4));
	if (lex->next->content[1] && !ft_strncmp("><", lex->next->content, 3))
		return (error_exec(RED_ERROR, 5));
	if (lex->next->content[1] && !ft_strncmp("<>", lex->next->content, 3))
		return (error_exec(RED_ERROR, 6));
	if (lex->next->content[0] == '>')
		return (error_exec(RED_ERROR, 0));
	if (lex->next->content[0] == '<')
		return (error_exec(RED_ERROR, 1));
}

void	error_red(t_lex *lex)
{
	while (lex)
	{
		if (!lex->content)
		{
			lex = lex->next;
			continue;
		}
		if (lex->content[0] == '<' && (!lex->next || !lex->next->content))
			return (error_exec(RED_ERROR, 7));
		if (lex->content[0] == '>' && (!lex->next || !lex->next->content))
			return (error_exec(RED_ERROR, 7));
		if (lex->content[1] && lex->content[0] == '>' && lex->content[1] == '<')
			return (error_exec(RED_ERROR, 5));
		if (lex->content[1] && lex->content[0] == '<' && lex->content[1] == '>')
			return (error_exec(RED_ERROR, 6));
		if ((lex->content[0] == '<' || lex->content[0] == '>') && \
			lex->next && lex->next->content &&
			(lex->next->content[0] == '<' || lex->next->content[0] == '>'))
			return (error_red2(lex));
		lex = lex->next;
	}
}

void	syntax_error(t_lex *lex)
{
	if (!lex)
		return ;
	error_red(lex);
	while (lex && lex->content == NULL)
		lex = lex->next;
	if (!lex)
		return ;
	if (lex->content[0] == '|')
		return (error_exec(PIPE_ERROR, 0));
	while (lex)
	{
		if (lex->content && lex->content[0] == '|')
		{
			if (!lex->previous || !lex->next || !lex->next->content)
				return (error_exec(PIPE_ERROR, 0));
			if ((lex->previous->content && lex->previous->content[0] == '|') ||
				(lex->next->content && lex->next->content[0] == '|'))
				return (error_exec(PIPE_ERROR, 0));
		}
		lex = lex->next;
	}
}