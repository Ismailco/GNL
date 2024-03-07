/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iscourr <i_courr@hotmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:31:14 by iscourr           #+#    #+#             */
/*   Updated: 2024/03/07 20:00:13 by iscourr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_readfile(int fd, char *string, char *buffer)
{
	char	*tmp;
	int		read_buffer;

	read_buffer = 1;
	while (read_buffer > 0)
	{
		read_buffer = read(fd, buffer, BUFFER_SIZE);
		if (read_buffer == -1)
		{
			free(string);
			return (NULL);
		}
		if (read_buffer == 0)
			break ;
		buffer[read_buffer] = '\0';
		if (!string)
			string = ft_strdup("");
		tmp = string;
		string = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (string);
}

char	*ft_freeline(char *string)
{
	char	*line;
	int		i;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (string[i] == '\0' || string[i + 1] == '\0')
		return (NULL);
	line = ft_substr(string, i + 1, ft_strlen(string) - i);
	if (*line == 0)
	{
		free(line);
		line = NULL;
	}
	string[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*strings[2565];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		free(strings[fd]);
		free(buffer);
		buffer = NULL;
		strings[fd] = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = ft_readfile(fd, strings[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	strings[fd] = ft_freeline(line);
	return (line);
}
