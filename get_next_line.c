/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:41:24 by loda-sil          #+#    #+#             */
/*   Updated: 2025/09/11 17:15:58 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_and_null(char *ptr)
{
	free(ptr);
	return (NULL);
}

char	*split_and_store(char *line)
{
	char	*next_line_content;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	next_line_content = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*next_line_content == '\0')
		return (free_and_null(next_line_content));
	line[i + 1] = '\0';
	return (next_line_content);
}

char	*read_until_newline(int fd, char *line_content, char *buffer)
{
	int		bytes_read;
	char	*old_content;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_and_null(line_content));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!line_content)
		{
			line_content = ft_strdup("");
			if (!line_content)
				return (NULL);
		}
		old_content = line_content;
		line_content = ft_strjoin(old_content, buffer);
		free(old_content);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line_content);
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
	line = read_until_newline(fd, cache, buffer);
	free(buffer);
	if (!line)
	{
		cache = NULL;
		return (NULL);
	}
	cache = split_and_store(line);
	return (line);
}
