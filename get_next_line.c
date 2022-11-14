/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouzi <mdouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:15:00 by mdouzi            #+#    #+#             */
/*   Updated: 2022/11/14 20:21:40 by mdouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
char	*ft_line(char *save)
{
	if(!save[0])
		return NULL;
	char	*line;
	int		i;
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] && save[i] == '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
		
	}
	if (save[i] && save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	
	return (line);
}

char	*new_line(char *save)
{
	if (!save[0])
	{
		free(save);
		return NULL;
	}
	char *res;
	int i;
	i = 0;
	int j;
	j = 0;
	while(save[i] && save[i] != '\n')
		i++;
	if(save[i] && save[i] == '\n')
		i++;
	if(!(res = (char *)calloc(sizeof(char) ,(ft_strlen(save) - i + 1))))
		return (NULL);
	while(save[i])
	{
		res[j] = save[i];
		i++;
		j++;
	}
	res[j] = '\0';
	free(save);
	return (res);
}

char *get_next_line(int fd)
{
	static char	*save;
	char		*buffer;
	int			rd;
	char		*line;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)
		return NULL;	
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if(rd == -1)
		{
			// if(save)
				free(save);
				save = 0;
			free(buffer);
			return NULL;
		}
		buffer[rd] = '\0';
		save = ft_strjoin(save, buffer);
		if(strchr(save,'\n'))
			break;
	}
	free(buffer);
	if(!save)
		return NULL;
	// printf("(((%s)))\n",line);
	// printf("(((%s)))\n",save);
		
	line = ft_line(save);
	
	save = new_line(save);
	return (line);
}


// int main()
// {
// 	int fd;
// 	fd = open("file.txt", O_RDONLY);
// 	printf("%s",get_next_line(fd));
	
// }	