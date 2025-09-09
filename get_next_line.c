/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:41:24 by loda-sil          #+#    #+#             */
/*   Updated: 2025/09/09 19:02:35 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_and_null(char *ptr)
{
	free(ptr);
	return (NULL);
}

char	*set_line(char *line)
{
	char	*cache;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	cache = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*cache == '\0')
		return (free_and_null(cache));
	line[i + 1] = '\0';
	return (cache);
}

char	*fill_line_buffer(int fd, char *cache, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_and_null(cache));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!cache)
		{
			cache = ft_strdup("");
			if (!cache)
				return (NULL);
		}
		temp = cache;
		cache = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(cache);
		free(buffer);
		cache = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = fill_line_buffer(fd, cache, buffer);
	free(buffer);
	if (!line)
	{
		cache = NULL;
		return (NULL);
	}
	cache = set_line(line);
	return (line);
}
