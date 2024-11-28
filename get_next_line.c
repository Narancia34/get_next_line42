/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:09:37 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/28 16:07:32 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *remainder)
{
	int		i;
	char	*line;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line = ft_memcpy(line, remainder, i);
	line[i] = '\0';
	return (line);
}

char	*get_remainder(char *str)
{
	char	*p;
	char	*remainder;

	if (!str)
		return (NULL);
	p = ft_strchr(str, '\n');
	if (!p)
		return (free(str), (NULL));
	remainder = ft_strdup(p + 1);
	free (str);
	return (remainder);
}

char	*read_file(char *remainder, int fd)
{
	ssize_t		bytes_read;
	char		*buffer;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), (NULL));
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	if (bytes_read == 0 && (!remainder || !*remainder))
		return (free(remainder), remainder = NULL);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	if (!ft_strchr(remainder, '\n'))
		remainder = read_file(remainder, fd);
	if (!remainder)
		return (free(remainder), NULL);
	line = get_line(remainder);
	remainder = get_remainder(remainder);
	return (line);
}
