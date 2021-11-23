/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 01:08:45 by abigeddi          #+#    #+#             */
/*   Updated: 2021/11/23 01:11:24 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_new_line(char *remain)
{
	int	i;

	i = 0;
	if (!remain)
		return (-1);
	while (remain[i])
	{
		if (remain[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_line(char *remain)
{
	char	*line;
	int		index;
	int		i;

	i = 0;
	if (ft_strlen(remain) <= 0)
		return (NULL);
	index = find_new_line(remain);
	if (index == -1)
	{
		line = ft_strdup(remain);
		return (line);
	}
	line = (char *)malloc((index + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (remain[i] != '\n')
	{
		line[i] = remain[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_remain(char *remain)
{
	int		len;
	int		index;
	char	*tmp;

	if (!remain)
		return (NULL);
	len = ft_strlen(remain);
	index = find_new_line(remain);
	if (index != -1)
	{
		tmp = ft_substr(remain, (index + 1), (len - index - 1));
		free (remain);
		remain = tmp;
		return (remain);
	}
	free (remain);
	return (NULL);
}

char	*ft_read_line(int fd, char *buff, char *remain)
{
	char	*tmp;
	int		n;

	n = 0;
	while (find_new_line(remain) == -1)
	{
		n = read (fd, buff, BUFFER_SIZE);
		if (n > 0)
		{
			buff[n] = '\0';
			tmp = ft_strjoin(remain, buff);
			if (remain)
				free(remain);
			remain = NULL;
			remain = tmp;
		}
		else
			break ;
	}
	free (buff);
	buff = NULL;
	if (n == -1)
		return (NULL);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain[1024];
	char		*line;
	char		*buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	remain[fd] = ft_read_line(fd, buff, remain[fd]);
	line = ft_line(remain[fd]);
	remain[fd] = ft_remain(remain[fd]);
	return (line);
}
