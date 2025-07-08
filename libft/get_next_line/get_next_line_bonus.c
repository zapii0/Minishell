/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:59:41 by apieniak          #+#    #+#             */
/*   Updated: 2025/03/27 14:21:10 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = my_calloc(ft_strlen_gnl(buffer) - i, 1);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*get_line_main(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = my_calloc(i + 2, 1);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*textf_read(char *buffer, int fd)
{
	char	*buff_supp;
	int		buff_count;

	if (!buffer)
		buffer = my_calloc(1, 1);
	buff_supp = my_calloc(BUFFER_SIZE + 1, 1);
	buff_count = read(fd, buff_supp, BUFFER_SIZE);
	while (buff_count > 0)
	{
		buff_supp[buff_count] = '\0';
		buffer = ft_strjoin_gnl(buffer, buff_supp);
		if (!buffer)
			free(buff_supp);
		if (!buffer)
			return (NULL);
		if (search_for_char(buffer, '\n'))
			break ;
		buff_count = read(fd, buff_supp, BUFFER_SIZE);
	}
	free(buff_supp);
	if (buff_count == -1)
		free(buffer);
	if (buff_count == -1)
		buffer = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	buffer[fd] = textf_read(buffer[fd], fd);
	if (!buffer[fd])
	{
		buffer[fd] = NULL;
		return (NULL);
	}
	line = get_line_main(buffer[fd]);
	buffer[fd] = next_line(buffer[fd]);
	return (line);
}

/*
int main()
{
	int fd = open("kiedy.txt", O_RDONLY);
	int fdb = open("cwl.txt", O_RDONLY);
	int fdc = open("frajer.txt", O_RDONLY);
	char *a;

	 while ((a = get_next_line(fd)))
	{
		printf("%s", a);
	}  
	while ((a = get_next_line(fdb)))
	{
		printf("%s", a);
	}  
	while ((a = get_next_line(fdc)))
	{
		printf("%s", a);
	}  
	return 0; 
}
*/