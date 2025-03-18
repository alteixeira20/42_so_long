/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:24:23 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/18 17:17:03 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	get_map_height(char *mapname)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		height++;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static char	**allocate_map_mem(int height)
{
	char	**map;

	map = malloc((height + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	return (map);
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static char	**prepare_map(int fd, int height)
{
	char	**map;
	char	*line;
	int		i;

	map = allocate_map_mem(height);
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line && i < height)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	if (!line && i < height)
	{
		free_map(map, i);
		return (NULL);
	}
	map[i] = NULL;
	return (map);
}

char	**read_map(char *mapname)
{
	int		fd;
	int		height;
	char	**map;

	height = get_map_height(mapname);
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (height <= 0)
		return (NULL);
	map = prepare_map(fd, height);
	close(fd);
	return (map);
}
