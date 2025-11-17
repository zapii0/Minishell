/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:52:46 by apieniak          #+#    #+#             */
/*   Updated: 2025/03/27 14:21:03 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/uio.h>

void	*my_calloc(int elements, int size);
int		search_for_char(char *str, char sign);
size_t	ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *src, char *dest);
char	*get_next_line(int fd);

#endif
