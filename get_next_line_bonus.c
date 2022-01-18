/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:24:33 by abazizi           #+#    #+#             */
/*   Updated: 2021/12/07 19:24:36 by abazizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*predup(int *index, char *buff)
{
	char	*tmp;

	buff[*index] = '\0';
	tmp = ft_strdup(buff);
	*index = 0;
	return (free(buff), tmp);
}

int	get_line(char *buff, int fd, int *index, char **tmp)
{
	int		ind;
	int		status;

	ind = 0;
	while (ind < BUFFER_SIZE && buff[*index - 1] != '\n')
	{
		status = read(fd, buff + *index, 1);
		if (status == -1 || (status == 0 && *index == 0))
		{
			*tmp = NULL;
			return (free(buff), -1);
		}
		if (status == 0)
		{
			*tmp = predup(index, buff);
			return (1);
		}
		ind++;
		(*index)++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static int	index = 0;
	char		*buff;
	char		*tmp;
	int			line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while ("AlwaysTrue")
	{
		line = get_line(buff, fd, &index, &tmp);
		if (line != 0)
			return (tmp);
		if (buff[index - 1] == '\n')
			return (predup(&index, buff));
		tmp = (char *)malloc((index + BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
			return (free(buff), NULL);
		ft_memcpy(tmp, buff, index);
		free(buff);
		buff = tmp;
	}
}
	