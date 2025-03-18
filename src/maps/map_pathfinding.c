/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:12:16 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/18 18:39:25 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	find_player(char **map, int *x, int *y)
{
	int		i;
	char	*pos;

	i = 0;
	while (map[i])
	{
		pos = ft_strchr(map[i], 'P');
		if (pos)
		{
			*x = pos - map[i];
			*y = i;
			return ;
		}
		i++;
	}
}

static void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static int	is_path_valid(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], 'C') || ft_strchr(map[i], 'E'))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_solvable(char **map)
{
	char	**dup;
	int		x;
	int		y;
	int		result;

	dup = duplicate_map(map);
	if (!dup)
		return (0);
	find_player(dup, &x, &y);
	flood_fill(dup, x, y);
	result = is_path_valid(dup);
	free_dup(dup);
	return (result);
}
