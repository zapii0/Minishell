/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:58:03 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 14:56:53 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words_count(char const *s, char c)
{
	int	counter;
	int	flag;
	int	i;

	counter = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			counter++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (counter);
}

static int	words_free(char **words, int current, size_t len)
{
	int	i;

	i = 0;
	words[current] = (char *)malloc(len);
	if (!words[current])
	{
		while (i < current)
		{
			free(words[i]);
			i++;
		}
		free(words);
		return (1);
	}
	return (0);
}

static int	words_fill(char **words, char const *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (words_free(words, i, len + 1))
				return (1);
			ft_strlcpy(words[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	words_amount;

	if (!s)
		return (NULL);
	words_amount = words_count(s, c);
	words = (char **)malloc((words_amount + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	words[words_amount] = NULL;
	if (words_fill(words, s, c))
		return (NULL);
	return (words);
}
